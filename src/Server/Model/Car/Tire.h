#ifndef MICROMACHINES_TIRE_H
#define MICROMACHINES_TIRE_H

#include <Box2D/Box2D.h>
#include "../Input.h"

//types of fixture user data
enum fixtureUserDataType {
    FUD_CAR_TIRE,
    FUD_GROUND_AREA
};

//a class to allow subclassing of different fixture user data
class FixtureUserData {
    fixtureUserDataType m_type;
protected:
    FixtureUserData(fixtureUserDataType type) : m_type(type) {}
public:
    virtual fixtureUserDataType getType() { return m_type; }
    virtual ~FixtureUserData() {}
};

//class to allow marking a fixture as a car tire
class CarTireFUD : public FixtureUserData {
public:
    CarTireFUD() : FixtureUserData(FUD_CAR_TIRE) {}
};

//class to allow marking a fixture as a ground area
class GroundAreaFUD : public FixtureUserData {
public:
    float frictionModifier;
    bool outOfCourse;

    GroundAreaFUD(float fm, bool ooc) : FixtureUserData(FUD_GROUND_AREA) {
        frictionModifier = fm;
        outOfCourse = ooc;
    }
};


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
