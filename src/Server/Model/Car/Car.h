#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include "../../../3rd-party/Box2D/Box2D.h"
#include "../Configuration.h"
#include "../FixtureUserData.h"
#include "../../../Common/Event/CommandEvent.h"
#include "../../../Common/Constants.h"
#include "../Track.h"
#include "../mods/DTOs.h"

#include "MovingState/CarMovingState.h"
#include "TurningState/CarTurningState.h"

enum StatusType {
    GRABBED_HEALTH_POWERUP,
    GRABBED_BOOST_POWERUP,
    GRABBED_MUD,
    GRABBED_ROCK,
    GRABBED_OIL,
    EXPLODED,
    WINNED,
    NOTHING
};

struct Status {
    StatusType status;
    int timeOfAction;
    size_t id;
};

class CarTurningState;
class CarMovingState;

class Car{
private:
    size_t _id;

    float _currentForwardSpeed;
    float _currentForwardDrive;
    float _currentBackwardSpeed;
    float _currentBackwardDrive;

    float _maxForwardSpeedOnGrass;
    float _maxForwardDriveOnGrass;
    float _maxBackwardSpeedOnGrass;
    float _maxBackwardDriveOnGrass;

    float _maxForwardSpeed;
    float _maxBackwardSpeed;
    float _maxForwardDrive;
    float _maxBackwardDrive;

    float _desiredTorque;
    float _maxLateralImpulse;
    float _maxAngularImpulse;
    float _angularImpulse;
    size_t _maxHealth;

    b2Fixture* _fixture;
    b2BodyDef _carBodyDef;
    b2Body* _carBody;
    std::shared_ptr<CarMovingState> _state;
    std::shared_ptr<CarTurningState> _turningState;
    bool _isMoving;
    bool _exploded;
    std::vector<std::shared_ptr<Status>> _status;

    size_t _maxLaps;
    size_t _maxtracksToLap;
    size_t _laps;

    int _health;
    float _previous_x, _previous_y, _previousAngle;

    GroundAreaFUD* _groundArea;
    std::vector<Track*> _tracks;
    bool _onGrass;

    bool _winner;
    std::shared_ptr<CarFUD> cFUD;

    void _setBodyDef(float& x_init, float& y_init, float& angle, const std::shared_ptr<Configuration>& configuration);
    void _setShapeAndFixture(const std::shared_ptr<Configuration>& configuration);

    void modifySpeed(const bool& onGrass, float& speedToModify, float& maxSpeedOnGrass, float& maxSpeedOnTrack,
                     float& driveToModify, float& maxDriveOnGrass, float& maxDriveOnTrack);

public:
    Car(const std::shared_ptr<b2World>& world, size_t& id, float& x_init, float& y_init, float angle,
        const size_t& max_tracks, const std::shared_ptr<Configuration>& configuration);

    Car(const Car &other) = delete;
    Car& operator=(const Car &other) = delete;

    void accelerate();
    void desaccelerate();
    void turnLeft();
    void turnRight();

    //Contact with floor
    void setTrack(Track* track);

    std::vector<std::shared_ptr<Status>> getStatus();
    void resetStatus();

    void addGroundArea(GroundAreaFUD* ga);
    void removeGroundArea(GroundAreaFUD* ga);
    void updateFriction();

    //Crashing
    void crash(b2Vec2 impactVel);

    //Modifiers
    void handleHealthPowerup(HealthPowerupFUD* hpu, const size_t& id);
    void handleBoostPowerup(BoostPowerupFUD* bpuFud, const size_t& id);
    void handleMud(MudFUD* mudFud, const size_t& id);
    void handleOil(OilFUD* oilFud, const size_t& id);
    void handleRock(RockFUD* rockFud, const size_t& id);

    void stopEffect(const int& effectType);

    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();

    void explode();
    void resetCar();

    virtual void handleInput(const InputEnum& input);
    virtual int update();

    const float x();
    const float y();
    const float angle();
    const float health();
    const float speed();
    const b2Vec2 linearVelocity();
    const bool onGrass();

    void assignId(int id);

    void carToDTO(CarDTO_t* carDTO);
    void dtoToModel(const CarDTO_t& carDTO);

    ~Car() = default;
};

#endif //MICROMACHINES_CAR_H
