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

void World::createTrack(std::vector<Track*>& track){
    std::ifstream i("scene.json");
    json j; i >> j;

    size_t id = 0;
    float x, y, angle;
    int type;

    json tracks = j["tracks"];
    for (auto& t : tracks){
        x = t["x"].get<float>();
        y = t["y"].get<float>();
        angle = t["angle"].get<float>();
        type = t["type"].get<float>();
        id++;
        Track* _track = new Track(_world, id, type, x, y, angle * DEGTORAD, _configuration);
        track.push_back(_track);
    }
}

void World::createGrass(std::vector<Grass*>& grass){
    std::ifstream i("scene.json");
    json j; i >> j;

    size_t id = 0;
    float x, y, angle;
    int type;

    json gr = j["grass"];
    for (auto& g : gr){
        x = g["x"].get<float>();
        y = g["y"].get<float>();
        angle = g["angle"].get<float>();
        type = g["type"].get<float>();
        id++;
        Grass* _grass = new Grass(_world, id, type, x, y, angle * DEGTORAD, _configuration);
        grass.push_back(_grass);
        //std::cout << "\nCreating grass x: " << x << " y: " << y << " angle: " << angle;
    }
}

HealthPowerup* World::createHealthPowerup(){
    std::ifstream i("scene.json");
    json j; i >> j;

    size_t id = 0;
    float x, y, angle;
    int type;

    json hpowerups = j["health_powerups"];
    for (auto& hp : hpowerups){
        type = hp["type"].get<int>();
        x = hp["x"].get<float>();
        y = hp["y"].get<float>();
        angle = hp["angle"].get<float>();

        return new HealthPowerup(_world, type, id, x, y, angle * DEGTORAD, _configuration);
    }
}

BoostPowerup* World::createBoostPowerup(){
    std::ifstream i("scene.json");
    json j; i >> j;

    size_t id = 0;
    float x, y, angle;
    int type;

    json bpowerups = j["boost_powerups"];
    x = bpowerups.at(0)["x"].get<float>();
    y = bpowerups.at(0)["y"].get<float>();
    angle = bpowerups.at(0)["angle"].get<float>();
    type = bpowerups.at(0)["type"].get<float>();

    return new BoostPowerup(_world, type, id, x, y, angle * DEGTORAD, _configuration);
}

void World::step(uint32_t velocityIt, uint32_t positionIt){
    //how strongly to correct velocity
    //how strongly to correct position
    _world->Step( _timeStep, velocityIt, positionIt);
    _world->ClearForces();
}

b2World* World::getWorld(){
    return _world;
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
