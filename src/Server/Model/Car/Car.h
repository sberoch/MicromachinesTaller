#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include "../../../3rd-party/Box2D/Box2D.h"

#include "../Configuration.h"
#include "../FixtureUserData.h"
#include "../../../Common/Event/CommandEvent.h"
#include "../../../Common/Constants.h"

enum Status {
    GRABBED_HEALTH_POWERUP,
    GRABBED_BOOST_POWERUP,
    GRABBED_ROCK,
    GRABBED_OIL,
    GRABBED_MUD,
    EXPLODED,
    CRASHED_INTO_CAR,
    NOTHING
};

class CarTurningState;
class CarMovingState;

class Car{
private:
    std::shared_ptr<Configuration> _configuration;

    float _maxForwardSpeed;
    float _maxBackwardSpeed;
    float _maxDriveForce;
    float _maxLateralImpulse;
    float _desiredTorque; //Maniovrability.

    size_t _id;
    b2Fixture* _fixture;
    b2BodyDef _carBodyDef;
    b2Body* _carBody;
    CarMovingState* _state;
    CarTurningState* _turningState;
    bool _isMoving;
    Status _status;

    //Floor friction
    b2FrictionJoint* _joint;
    b2FrictionJointDef _jointDef;
    bool _createJoint;

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
    void turnLeft();
    void turnRight();

    //Contact with floor
    void startContact(b2Body* ground);
    void endContact(b2Body* ground);
    void createFrictionJoint();
    void destroyFrictionJoint();

    void addGroundArea(GroundAreaFUD* ga);
    void removeGroundArea(GroundAreaFUD* ga);
    void updateTraction();
    void updateFriction();

    //Crashing
    void crash(b2Vec2 impactVel);

    //Modifiers
    void handleHealthPowerup();
    void handleBoostPowerup();
    void handleMud(MudFUD* mudFud);
    void handleOil(OilFUD* oilFud);
    void handleRock(RockFUD* rockFud);

    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();

    void resetCar();
    Status getStatus();

    virtual void handleInput(const InputEnum& input);
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
    static CarMovingState* makeMovingState(const InputEnum& input);
    virtual CarMovingState* handleInput(Car& car, const InputEnum& input) = 0;
    virtual void update(Car& car) = 0;
    virtual ~CarMovingState(){}
};

class CarTurningState {
public:
    static CarTurningState* makeTurningState(const InputEnum& input);
    virtual CarTurningState* handleInput(Car& car, const InputEnum& input) = 0;
    virtual void update(Car& car) = 0;
    virtual ~CarTurningState(){}
};

#endif //MICROMACHINES_CAR_H
