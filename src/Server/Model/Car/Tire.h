#ifndef MICROMACHINES_TIRE_H
#define MICROMACHINES_TIRE_H

#include <Box2D/Box2D.h>
#include "../Input.h"
#include "../FixtureUserData.h"

class Tire {
private:
    b2BodyDef _bodyDef;
    b2Body* _body;

    float _maxForwardSpeed;
    float _maxBackwardSpeed;
    float _maxDriveForce;
    GroundAreaFUD* _groundArea;
    float _currentTraction;

public:
    Tire(b2World* world, float maxForwardSpeed, float maxBackwardSpeed, float madDriveForce);

    void addGroundArea(GroundAreaFUD* ga);
    void removeGroundArea(GroundAreaFUD* ga);

    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();
    void updateTraction();
    void updateFriction();
    void updateDrive(int controlState);
    void updateTurn(int controlState);
    ~Tire();
};

#endif //MICROMACHINES_TIRE_H
