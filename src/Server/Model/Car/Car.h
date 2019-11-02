#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include "../../../3rd-party/Box2D/Box2D.h"

#include "../Input.h"
#include "../Configuration.h"
#include "../FixtureUserData.h"

class CarTurningState;
class CarMovingState;

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class Car {
private:
    float _maxForwardSpeed;
    float _maxBackwardSpeed;
    float _maxDriveForce;

    size_t _id;
    b2Fixture* _fixture;
    b2BodyDef _carBodyDef;
    b2Body* _carBody;
    CarMovingState* _state;
    CarTurningState* _turningState;
    bool _isMoving;

    //Floor friction
    b2FrictionJoint* _joint;
    b2FrictionJointDef _jointDef;

    int _health;
    float _previous_x, _previous_y;

    GroundAreaFUD* _groundArea;
    float _currentTraction;

    void _setBodyDef(float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration);
    void _setShapeAndFixture(std::shared_ptr<Configuration> configuration);

public:
    //Car(b2Body* carBody);
    Car(b2World* world, size_t id, float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration);

    Car(const Car &other) = delete;
    Car& operator=(const Car &other) = delete;
    Car(Car&& other);
    Car& operator=(Car&& other);

    void accelerate();
    void desaccelerate();
    void friction();
    void turnLeft();
    void turnRight();

    //Contact with floor
    void addGroundArea(GroundAreaFUD* ga);
    void removeGroundArea(GroundAreaFUD* ga);
    void updateTraction();
    void updateFriction();

    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();

    void resetCar();

    virtual void handleInput(Input movInput, Input turnInput);
    virtual void update();

    const float x();
    const float y();
    const float angle();
    const float health();
    const float speed();
    const b2Vec2 linearVelocity();
    b2Body* body() const;

    ~Car();
};

class CarMovingState{
public:
    static CarMovingState* makeMovingState(Input prevInput, Input currentInput);
    virtual CarMovingState* handleInput(Car& car, Input input) = 0;
    virtual void update(Car& car) = 0;
    virtual ~CarMovingState(){}
};

class CarTurningState {
public:
    static CarTurningState* makeTurningState(Input prevInput, Input currentInput);
    virtual CarTurningState* handleInput(Car& car, Input input) = 0;
    virtual void update(Car& car) = 0;
    virtual ~CarTurningState(){}
};

#endif //MICROMACHINES_CAR_H
