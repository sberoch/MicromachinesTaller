#ifndef MICROMACHINES_FIXTUREUSERDATA_H
#define MICROMACHINES_FIXTUREUSERDATA_H

//types of fixture user data
enum fixtureUserDataType {
    FUD_CAR,
    FUD_GROUND_AREA,
    FUD_HEALTH_POWERUP,
    FUD_BOOST_POWERUP,
    FUD_OIL,
    FUD_MUD,
    FUD_ROCK
};

//a class to allow subclassing of different fixture user data
class FixtureUserData {
    fixtureUserDataType m_type;
    size_t _id;
protected:
    FixtureUserData(fixtureUserDataType type, size_t id) : m_type(type), _id(id) {}
public:
    virtual fixtureUserDataType getType() { return m_type; }
    virtual size_t getId() { return _id; }
    virtual ~FixtureUserData() {}
};

//class to allow marking a fixture as a car
class CarFUD : public FixtureUserData {
public:
    CarFUD(size_t id) : FixtureUserData(FUD_CAR, id) {}
};

//class to allow marking a fixture as a ground area
class GroundAreaFUD : public FixtureUserData {
public:
    float frictionModifier;
    bool grass;

    GroundAreaFUD(float fm, bool grass, size_t id) : FixtureUserData(FUD_GROUND_AREA, id), grass(grass){
        frictionModifier = fm;
    }

    bool isGrass(){
        return grass;
    }
};

class HealthPowerupFUD : public FixtureUserData {
private:
    int _healthToIncrease;

public:
    HealthPowerupFUD(size_t id, int healthToIncrease) : FixtureUserData(FUD_HEALTH_POWERUP, id),
                                                        _healthToIncrease(healthToIncrease) {}

    int getHealthToIncrease(){
        return _healthToIncrease;
    }
};

class BoostPowerupFUD : public FixtureUserData {
public:
    float time;
    float _speedToIncrease;
    float _newDrive;

    BoostPowerupFUD(float time, float speedToIncrease, float newDrive, size_t& id) :
                    FixtureUserData(FUD_BOOST_POWERUP, id),
                    time(time), _speedToIncrease(speedToIncrease), _newDrive(newDrive) {}

    float getActionTime(){
        return time;
    }

    float getSpeedToIncrease(){
        return _speedToIncrease;
    }

    float getNewDrive(){
        return _newDrive;
    }
};

class OilFUD : public FixtureUserData {
public:
    float damping;
    float time;

    OilFUD(float damping, float time, size_t id) : FixtureUserData(FUD_OIL, id), damping(damping), time(time) {}

    float getDamping(){
        return damping;
    }

    float getActionTime(){
        return time;
    }
};

class MudFUD : public FixtureUserData {
public:
    float time;

    MudFUD(float time, size_t id) : FixtureUserData(FUD_MUD, id), time(time) {}

    float getActionTime() {
        return time;
    }
};

class RockFUD : public FixtureUserData {
public:
    float velToReduce;
    float healthToReduce;
    int _timeOfAction;
    int _driveToReduce;

    RockFUD(float velToReduce, float healthToReduce, int driveToReduce, int timeOfAction, size_t id) :
            FixtureUserData(FUD_ROCK, id), velToReduce(velToReduce),
            healthToReduce(healthToReduce), _driveToReduce(driveToReduce), _timeOfAction(timeOfAction) {}

    float getVelToReduce(){
        return velToReduce;
    }

    float getHealthToReduce(){
        return healthToReduce;
    }

    int getTimeOfAction(){
        return _timeOfAction;
    }

    int getDriveToReduce(){
        return _driveToReduce;
    }
};

#endif //MICROMACHINES_FIXTUREUSERDATA_H