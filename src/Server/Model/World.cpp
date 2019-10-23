#include <fstream>
#include "World.h"

#include "../json/json.hpp"

using json = nlohmann::json;

World::World(size_t n_of_cars) : _n_of_cars(n_of_cars){
    b2Vec2 gravity(0, -9.8);
    _world = new b2World(gravity);

    _carBodyDef.type = b2_dynamicBody;
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
