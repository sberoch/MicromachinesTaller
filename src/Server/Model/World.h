#ifndef MICROMACHINES_WORLD_H
#define MICROMACHINES_WORLD_H

#include <Box2D/Box2D.h>
#include "src/Server/Model/Car/Car.h"

class World {
private:
    b2World* _world;
    float _timeStep = 1/30.0;

    int _n_of_cars;
    b2BodyDef _carBodyDef; //What can we do with this?
    void _getCarConfigData(size_t id, float& x, float& y, float& angle);

    b2BodyDef _track_body_def;

    void _createTrack(float x, float y, float angle);
    void _setUpTrack(std::string track_config_file);

public:
    World(size_t n_of_cars);

    b2Body* createCar(size_t id);
    void step(uint32_t velocityIt, uint32_t positionIt);

    ~World();
};


#endif //MICROMACHINES_WORLD_H
