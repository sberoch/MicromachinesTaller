#include <fstream>
#include "World.h"
#include "../json/json.hpp"
#include <iostream>
#include <memory>

using json = nlohmann::json;

World::World(size_t n_of_cars, const std::shared_ptr<Configuration>& configuration) :
        _timeStep(1/configuration->getFPS()), _n_of_cars(n_of_cars), _configuration(configuration),
        _cars(), _track(), _grass(), _activeModifiers(), _modifierType(), _maxId(0) {
    b2Vec2 gravity(configuration->getGravityX(), configuration->getGravityY());
    _world = std::make_shared<b2World>(gravity);

    _contactListener = std::make_shared<ContactListener>(_world);
    _world->SetContactListener(_contactListener.get());

    _destructionListener = new DestructionListener();
    _world->SetDestructionListener(_destructionListener);

    createTrack();
    createGrass();

    _modifierType.push_back(TYPE_HEALTH_POWERUP);
    _modifierType.push_back(TYPE_BOOST_POWERUP);
    _modifierType.push_back(TYPE_ROCK);
    _modifierType.push_back(TYPE_OIL);
    _modifierType.push_back(TYPE_MUD);
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

std::shared_ptr<Car> World::createCar(size_t id, json j){
    float x_init, y_init, angle_init;

    json cars = j["cars"];
    json car = getCarById(id, cars);

    x_init = car["x_init"].get<float>();
    y_init = car["y_init"].get<float>();
    angle_init = car["angle"].get<float>();

    std::shared_ptr<Car> newCar(new Car(_world, id, x_init, y_init, angle_init * DEGTORAD, _track.size(),_configuration));
    _cars.push_back(newCar);
    return newCar;
}

void World::createTrack(){
    std::ifstream i("map2.json");
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
        std::shared_ptr<Track> track(new Track(_world, id, type, x, y, angle * DEGTORAD, _configuration));
        _track.push_back(track);
    }

    _track[0]->setAsStart();
    _track[_track.size()-1]->setAsFinish();
}

void World::createGrass(){
    std::ifstream i("map2.json");
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
        std::shared_ptr<Grass> grass(new Grass(_world, id, type, x, y, angle * DEGTORAD, _configuration));
        _grass.push_back(grass);
    }
}

json World::getSerializedMap() {
    std::ifstream i("map2.json");
    json j; 
    i >> j;
    return j;
}

void World::_removeGrabbedModifiers(){
    std::vector<std::shared_ptr<Modifier>> aux;
    for (size_t i=0; i<_activeModifiers.size(); ++i){
        std::shared_ptr<Modifier> modifier = _activeModifiers[i];
        if (!modifier->toDelete())
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
                if (distance < minDistance)
                    minDistance = distance;
            }

            if (minDistance >= _configuration->getMaxDistToTrack())
                _car->resetCar();
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

World::~World()= default;

void World::toDTO(WorldDTO_t* world){
    for (size_t i=0; i<_cars.size(); ++i)
        _cars[i]->carToDTO(&world->cars[i]);
    world->cars_size = _cars.size();

    for (size_t i=0; i<_track.size(); ++i)
        _track[i]->toDTO(&world->track[i]);
    world->track_size = _track.size();

    for (size_t i=0; i<_activeModifiers.size(); ++i){
        _activeModifiers[i]->toDTO(&world->modifiers[i]);
    }

    for (size_t i=_activeModifiers.size(); i<MAX_MODIFIERS; ++i){
        world->modifiers[i].active = false;
    }
}

void World::dtoToModel(WorldDTO_t* worldDTO) {
    for (size_t i=0; i<_cars.size(); ++i){
        _cars[i]->dtoToModel(worldDTO->cars[i]);
    }

    for (size_t i=0; i<MAX_MODIFIERS; ++i){
        ModifierDTO modifier = worldDTO->modifiers[i];
        if (modifier.newModifier){
            _activeModifiers.push_back(Modifier::makeModifier(_world, modifier.type, modifier.id, modifier.x, modifier.y,
                                                              modifier.angle * DEGTORAD, _configuration));
        }
    }
}