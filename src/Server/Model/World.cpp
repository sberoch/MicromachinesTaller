#include <fstream>
#include "World.h"
#include "../json/json.hpp"
#include <iostream>

using json = nlohmann::json;

World::World(size_t n_of_cars, std::shared_ptr<Configuration> configuration) :
             _timeStep(1/25.0), _n_of_cars(n_of_cars), _configuration(configuration),
              _track(), _grass() {
    b2Vec2 gravity(configuration->getGravityX(), configuration->getGravityY());
    _world = new b2World(gravity);

    _contactListener = new ContactListener(_world);
    _world->SetContactListener(_contactListener);

    createTrack(_track);
    createGrass(_grass);
    _activeModifiers.push_back(createHealthPowerup());
    _activeModifiers.push_back(createBoostPowerup());
    _activeModifiers.push_back(createMud());
    _activeModifiers.push_back(createRock());
    _activeModifiers.push_back(createOil());
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
    }
}

json World::getSerializedMap() {
    std::ifstream i("scene.json");
    json j; 
    i >> j;
    return j;
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

        Modifier::makeModifier(_world, type, id, x, y, angle * DEGTORAD, _configuration);
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

    Modifier::makeModifier(_world, type, id, x, y, angle * DEGTORAD, _configuration);
}

Mud* World::createMud(){
    std::ifstream i("scene.json");
    json j; i >> j;

    size_t id = 0;
    float x, y, angle;
    int type;

    json muds = j["muds"];
    x = muds.at(0)["x"].get<float>();
    y = muds.at(0)["y"].get<float>();
    angle = muds.at(0)["angle"].get<float>();
    type = muds.at(0)["type"].get<float>();

    Modifier::makeModifier(_world, type, id, x, y, angle * DEGTORAD, _configuration);
}

Oil* World::createOil(){
    std::ifstream i("scene.json");
    json j; i >> j;

    size_t id = 0;
    float x, y, angle;
    int type;

    json oils = j["oils"];
    x = oils.at(0)["x"].get<float>();
    y = oils.at(0)["y"].get<float>();
    angle = oils.at(0)["angle"].get<float>();
    type = oils.at(0)["type"].get<float>();

    Modifier::makeModifier(_world, type, id, x, y, angle * DEGTORAD, _configuration);
}

Rock* World::createRock(){
    std::ifstream i("scene.json");
    json j; i >> j;

    size_t id = 0;
    float x, y, angle;
    int type;

    json rocks = j["rocks"];
    x = rocks.at(0)["x"].get<float>();
    y = rocks.at(0)["y"].get<float>();
    angle = rocks.at(0)["angle"].get<float>();
    type = rocks.at(0)["type"].get<float>();

    Modifier::makeModifier(_world, type, id, x, y, angle * DEGTORAD, _configuration);
}

void World::createRandomModifier(size_t& type, size_t& id, float& x, float& y, float& angle){
    int rand = std::rand() % _track.size();
    Track* randomTrack = _track[rand];
    x = randomTrack->x();
    y = randomTrack->y();
    angle = randomTrack->angle();
    type = randomTrack->type();

    id = _activeModifiers.size();

    _activeModifiers.push_back(Modifier::makeModifier(_world, type, id, x, y, angle * DEGTORAD, _configuration));
    std::cout << "\nCreating a " << type;
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

