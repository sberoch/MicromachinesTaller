#include <fstream>
#include "World.h"

#include "../json/json.hpp"
#include <iostream>

using json = nlohmann::json;

World::World(size_t n_of_cars, std::shared_ptr<Configuration> configuration) :
            _timeStep(1/25.0), _n_of_cars(n_of_cars), _configuration(configuration){
    b2Vec2 gravity(configuration->getGravityX(), configuration->getGravityY());
    _world = new b2World(gravity);

    _contactListener = new ContactListener(_world);
    _world->SetContactListener(_contactListener);
}

void World::_getCarConfigData(size_t id, float& x, float& y, float& angle){
    std::ifstream i("scene.json");
    json j; i >> j;

    json cars = j["cars"];
    x = cars.at(id)["x_init"].get<float>();
    y = cars.at(id)["y_init"].get<float>();
    angle = cars.at(id)["angle"].get<float>();
    //Exception if accesing more than we have?
}

Car* World::createCar(size_t id){
    float x_init, y_init, angle_init;
    _getCarConfigData(id, x_init, y_init, angle_init);

    //return std::move(Car(_world, id, x_init, y_init, angle_init * DEGTORAD, _configuration));
    return new Car(_world, id, x_init, y_init, angle_init * DEGTORAD, _configuration);
}

std::vector<Track*> World::createTrack(){
    std::vector<Track*> track;

    std::ifstream i("scene.json");
    json j; i >> j;
    size_t id = 0;
    float x, y, angle;
    int type;

    json tracks = j["tracks"];
    for (auto t : tracks){
        x = t["x"].get<float>();
        y = t["y"].get<float>();
        angle = t["angle"].get<float>();
        type = t["type"].get<float>();
        id++;
        Track* _track = new Track(_world, id, type, x, y, angle * DEGTORAD, _configuration);
        track.push_back(_track);
    }

    return track;
}

void World::step(uint32_t velocityIt, uint32_t positionIt){
    //how strongly to correct velocity
    //how strongly to correct position
    _world->Step( _timeStep, velocityIt, positionIt);
    _world->ClearForces();
}

World::~World(){
    b2Body* node = _world->GetBodyList();
    while (node){
        b2Body* b = node;
        node = node->GetNext();
        _world->DestroyBody(b);
    }

    delete _world;
}


void World::BeginContact(b2Contact* contact){
    handleContact(contact, true);
}

void World::EndContact(b2Contact* contact){
    handleContact(contact, false);
}

void World::_tire_vs_groundArea(b2Fixture* tireFixture, b2Fixture* groundAreaFixture, bool began){
//    Tire* tire = (Tire*)tireFixture->GetBody()->GetUserData();
    GroundAreaFUD* gaFud = (GroundAreaFUD*)groundAreaFixture->GetUserData();
    //if (began)
        //tire->addGroundArea(gaFud);
    //else
        //tire->removeGroundArea(gaFud);
}

void World::handleContact(b2Contact* contact, bool began){
    b2Fixture* a = contact->GetFixtureA();
    b2Fixture* b = contact->GetFixtureB();
    FixtureUserData* fudA = (FixtureUserData*)a->GetUserData();
    FixtureUserData* fudB = (FixtureUserData*)b->GetUserData();

    if (!fudA || !fudB)
        return;

    if (fudA->getType() == FUD_CAR_TIRE || fudB->getType() == FUD_GROUND_AREA)
        _tire_vs_groundArea(a, b, began);
    else if (fudA->getType() == FUD_GROUND_AREA || fudB->getType() == FUD_CAR_TIRE)
        _tire_vs_groundArea(b, a, began);
}

b2World* World::getWorld(){
    return _world;
}