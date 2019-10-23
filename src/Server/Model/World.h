#ifndef MICROMACHINES_WORLD_H
#define MICROMACHINES_WORLD_H

#include <Box2D/Box2D.h>
#include "Car.h"

class World {
private:
    b2World* _world;
    float _timeStep = 1/30.0;

    int _n_of_cars;
    b2BodyDef _carBodyDef; //What can we do with this?
    void _getCarPosition(float& x, float& y);

public:
    World();

    b2Body* createCar();
    void step(uint32_t velocityIt, uint32_t positionIt);

    ~World();
};


#endif //MICROMACHINES_WORLD_H
