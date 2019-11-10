#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include "../../../3rd-party/Box2D/Box2D.h"
#include "../Configuration.h"
#include "../FixtureUserData.h"
#include "../../../Common/Event/CommandEvent.h"
#include "../../../Common/Constants.h"
#include "../Track.h"

enum Status {
    GRABBED_HEALTH_POWERUP,
    GRABBED_BOOST_POWERUP,
    GRABBED_MUD,
    GRABBED_ROCK,
    GRABBED_OIL,
    EXPLODED,
    NOTHING
};

struct State {
    Status status;
    int timeOfAction;
    size_t id;
};

class CarTurningState;
class CarMovingState;

class Car{
private:
    float _maxForwardSpeed;
    float _maxBackwardSpeed;
    float _maxDriveForce;
    float _desiredTorque;

    size_t _id;
    b2Fixture* _fixture;
    b2BodyDef _carBodyDef;
    b2Body* _carBody;
    CarMovingState* _state;
    CarTurningState* _turningState;
    bool _isMoving;
    bool _exploded;
    State _status;

    size_t _maxLaps;
    size_t _maxtracksToLap;
    size_t _tracksCounted;

    int _health;
    float _previous_x, _previous_y, _previousAngle;

    GroundAreaFUD* _groundArea;
    float _currentTraction;
    Track* _currentTrack;

    bool _winner;

    void _setBodyDef(float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration);
    void _setShapeAndFixture(std::shared_ptr<Configuration> configuration);

public:
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
    void setTrack(Track* track);

    State getStatus();
    void resetStatus();

    void addGroundArea(GroundAreaFUD* ga);
    void removeGroundArea(GroundAreaFUD* ga);
    void updateTraction();
    void updateFriction();

    //Crashing
    void crash(b2Vec2 impactVel);

    //Modifiers
    void handleHealthPowerup(size_t id);
    void handleBoostPowerup(BoostPowerupFUD* bpuFud, size_t id);
    void handleMud(MudFUD* mudFud, size_t id);
    void handleOil(OilFUD* oilFud, size_t id);
    void handleRock(RockFUD* rockFud, size_t id);

    void stopEffect(const int& effectType);

    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();

    void resetCar();

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
