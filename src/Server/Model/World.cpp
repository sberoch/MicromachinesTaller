#include <fstream>
#include "World.h"

#include "../json.hpp"

using json = nlohmann::json;

World::World() : _n_of_cars(0){
    b2Vec2 gravity(0, -9.8);
    _world = new b2World(gravity);

    _carBodyDef.type = b2_dynamicBody;
    _carBodyDef.angle = 0;
}

void World::_getCarPosition(float& x, float& y){
    int id, x_init, y_init, angle;
	std::ifstream i("scene.json");
	json j; i >> j;

	json cars = j["cars"];
	for (auto& car : cars){
		id = obj["type"].get<int>();

		angle = obj["angle"].get<int>();
	}
}

b2Body* World::createCar(){
    float x;
    float y;
    _getCarPosition(x, y);
    _carBodyDef.position.Set(x, y);

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
