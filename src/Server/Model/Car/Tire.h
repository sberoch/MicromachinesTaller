#ifndef MICROMACHINES_TIRE_H
#define MICROMACHINES_TIRE_H

#include <Box2D/Box2D.h>

class Tire {
private:
    b2BodyDef _bodyDef;
    b2Body* _body;

    float _maxSpeed;

public:
    Tire(b2World* world);
    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();
    void updateFriction();
    ~Tire();
};

#endif //MICROMACHINES_TIRE_H
