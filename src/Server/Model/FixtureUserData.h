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
    bool outOfCourse;
    bool grass;

    GroundAreaFUD(float fm, bool ooc, bool grass, size_t id) : FixtureUserData(FUD_GROUND_AREA, id) {
        frictionModifier = fm;
        outOfCourse = ooc;
        grass = grass;
    }

    bool isGrass(){
        return grass;
    }
};

class HealthPowerupFUD : public FixtureUserData {
public:
    HealthPowerupFUD(size_t id) : FixtureUserData(FUD_HEALTH_POWERUP, id) {}
};

class BoostPowerupFUD : public FixtureUserData {
public:
    BoostPowerupFUD(size_t id) : FixtureUserData(FUD_BOOST_POWERUP, id) {}
};

class OilFUD : public FixtureUserData {
public:
    OilFUD(size_t id) : FixtureUserData(FUD_OIL, id) {}
};

class MudFUD : public FixtureUserData {
public:
    MudFUD(size_t id) : FixtureUserData(FUD_MUD, id) {}
};

class RockFUD : public FixtureUserData {
public:
    RockFUD(size_t id) : FixtureUserData(FUD_ROCK, id) {}
};

#endif //MICROMACHINES_FIXTUREUSERDATA_H
