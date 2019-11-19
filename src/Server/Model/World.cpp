#include <fstream>
#include "World.h"
#include "../json/json.hpp"
#include <iostream>

using json = nlohmann::json;

World::World(size_t n_of_cars, std::shared_ptr<Configuration> configuration) :
             _timeStep(1/configuration->getFPS()), _n_of_cars(n_of_cars), _configuration(configuration),
             _cars(), _track(), _grass(), _activeModifiers(), _modifierType(), _maxId(0) {
    b2Vec2 gravity(configuration->getGravityX(), configuration->getGravityY());
    _world = new b2World(gravity);

    _contactListener = new ContactListener(_world);
    _world->SetContactListener(_contactListener);

    createTrack(_track);
    createGrass(_grass);

    _modifierType.push_back(TYPE_HEALTH_POWERUP);
    _modifierType.push_back(TYPE_BOOST_POWERUP);
    _modifierType.push_back(TYPE_ROCK);
    _modifierType.push_back(TYPE_OIL);
    _modifierType.push_back(TYPE_MUD);
}

void World::_getCarConfigData(size_t id, float& x, float& y, float& angle){
    std::ifstream i("scene.json");
    json j;
    i >> j;

    json cars = j["cars"];
    x = cars.at(id)["x_init"].get<float>();
    y = cars.at(id)["y_init"].get<float>();
    angle = cars.at(id)["angle"].get<float>();
}

json World::getCarById(int id, json cars){
    json carFound;

    for (auto& actualCar: cars){
        if (actualCar["id_from_room"] == id){
            carFound = actualCar;
        }
    }
    return carFound;
}

Car* World::createCar(size_t id, json j){
    float x_init, y_init, angle_init;
    //_getCarConfigData(id, x_init, y_init, angle_init);
    json cars = j["cars"];
    json car = getCarById(id, cars);

    x_init = car["x_init"].get<float>();
    y_init = car["y_init"].get<float>();
    angle_init = car["angle"].get<float>();

    Car* newCar = new Car(_world, id, x_init, y_init, angle_init * DEGTORAD, _configuration);
    _cars.push_back(newCar);
    return newCar;
}

void World::createTrack(std::vector<Track*>& track){
    std::ifstream i("map1.json");
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

    track[0]->setAsStart();
    track[track.size()-1]->setAsFinish();
}

void World::createGrass(std::vector<Grass*>& grass){
    std::ifstream i("map1.json");
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
    std::ifstream i("map1.json");
    json j; 
    i >> j;
    return j;
}

void World::createRandomModifier(size_t& type, size_t& id, float& x, float& y, float& angle){
    int rand = std::rand() % _track.size();
    Track* randomTrack = _track[rand];

    float xhi = randomTrack->x() - 2.5f;
    float xlo = randomTrack->x() + 2.5f;

    float yhi = randomTrack->y() - 2.5f;
    float ylo = randomTrack->y() + 2.5f;

    x = xlo + static_cast <float> (std::rand()) /( static_cast <float> (RAND_MAX/(xhi-xlo)));
    y = ylo + static_cast <float> (std::rand()) /( static_cast <float> (RAND_MAX/(yhi-ylo)));
    angle = randomTrack->angle();

    int modifierType = std::rand() % _modifierType.size();
    type = _modifierType[modifierType];

    id = _maxId;
    _maxId++;

    _activeModifiers.push_back(Modifier::makeModifier(_world, type, id, x, y, angle * DEGTORAD, _configuration));
}

void World::_removeGrabbedModifiers(){
    std::vector<Modifier*> aux;
    for (size_t i=0; i<_activeModifiers.size(); ++i){
        Modifier* modifier = _activeModifiers[i];
        if (modifier->toDelete())
            delete modifier;
        else
            aux.push_back(modifier);
    }
    _activeModifiers.swap(aux);
}

void World::_updateCarsOnGrass(){
    for (auto & _car : _cars){
        if (_car->onGrass()){
            float minDistance = _configuration->getMaxDistToTrack();
            for (auto & j : _track){
                float distance = j->getDistance(_car->x(), _car->y());
                if (distance < minDistance) {
                    minDistance = distance;
                }
            }

            if (minDistance > _configuration->getMaxDistToTrack()){
                _car->resetCar();
            }
        }
    }
}

void World::step(uint32_t velocityIt, uint32_t positionIt){
    //how strongly to correct velocity and position
    _world->Step( _timeStep, velocityIt, positionIt);
    _world->ClearForces();

    _removeGrabbedModifiers();
    _updateCarsOnGrass();
}

World::~World(){
    b2Body* node = _world->GetBodyList();
//    while (node){
//        b2Body* b = node;
//        node = node->GetNext();
//        _world->DestroyBody(b);
//    }

    delete _world;
}

