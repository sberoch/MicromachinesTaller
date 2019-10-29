#include <fstream>
#include "Car/Tire.h"
#include "World.h"

#include "../json/json.hpp"
#include <iostream>

using json = nlohmann::json;

void World::_createTrack(float x, float y, float angle){
    b2BodyDef floor_body_def;
    floor_body_def.position.Set(x, y);
    floor_body_def.angle = angle;

    b2Body* floor_body = _world->CreateBody(&floor_body_def);
}

void World::_setUpTrack(std::string track_config_file){
    std::ifstream i(track_config_file);
    json j; i >> j;
    float x, y, angle;

    json tracks = j["world1"];
    for (auto& track : tracks){
        x = tracks["x"].get<float>();
        y = tracks["y"].get<float>();
        angle = tracks["angle"].get<float>() * DEGTORAD;
        _createTrack(x, y, angle);
    }
}

World::World(size_t n_of_cars) : _n_of_cars(n_of_cars){
    b2Vec2 gravity(0, 0);
    _world = new b2World(gravity);

    _carBodyDef.type = b2_dynamicBody;
    _carBodyDef.linearDamping = 0.1f;

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

b2Body* World::createCar(size_t id){
    float x_init, y_init, angle_init;
    _getCarConfigData(id, x_init, y_init, angle_init);
    _carBodyDef.position.Set(x_init, y_init);
    _carBodyDef.angle = angle_init;

    b2Body* carBody;
    carBody = _world->CreateBody(&_carBodyDef);

    return carBody;
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
    Tire* tire = (Tire*)tireFixture->GetBody()->GetUserData();
    GroundAreaFUD* gaFud = (GroundAreaFUD*)groundAreaFixture->GetUserData();
    if (began)
        tire->addGroundArea(gaFud);
    else
        tire->removeGroundArea(gaFud);
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