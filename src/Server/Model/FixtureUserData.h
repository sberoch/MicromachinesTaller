#ifndef MICROMACHINES_FIXTUREUSERDATA_H
#define MICROMACHINES_FIXTUREUSERDATA_H

//types of fixture user data
enum fixtureUserDataType {
    FUD_CAR,
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
class CarFUD : public FixtureUserData {
public:
    CarFUD() : FixtureUserData(FUD_CAR) {}
};

//class to allow marking a fixture as a ground area
class GroundAreaFUD : public FixtureUserData {
public:
    float frictionModifier;
    bool outOfCourse;
    bool grass;

    GroundAreaFUD(float fm, bool ooc, bool grass) : FixtureUserData(FUD_GROUND_AREA) {
        frictionModifier = fm;
        outOfCourse = ooc;
        grass = grass;
    }

    bool isGrass(){
        return grass;
    }
};


#endif //MICROMACHINES_FIXTUREUSERDATA_H
