#ifndef MICROMACHINES_WORLD_H
#define MICROMACHINES_WORLD_H

#define DEGTORAD 0.0174532925199432957f

#include <Box2D/Box2D.h>
#include "Car/Car.h"
#include "ContactListener.h"
#include "Track.h"
#include "FixtureUserData.h"
#include "Grass.h"
#include "Modifier.h"

class World {
private:
    b2World* _world;
    float _timeStep;
    std::shared_ptr<Configuration> _configuration;

    int _n_of_cars;
    void _getCarConfigData(size_t id, float& x, float& y, float& angle);

    //Floor
    b2BodyDef _track_body_def;
    ContactListener* _contactListener;

public:
    World(size_t n_of_cars, std::shared_ptr<Configuration> configuration);

    void createTrack(std::vector<Track*>& track);
    void createGrass(std::vector<Grass*>& grass);
    Car* createCar(size_t id); //TODO move

    //Modifiers
    HealthPowerup* createHealthPowerup();
    BoostPowerup* createBoostPowerup();

    void step(uint32_t velocityIt, uint32_t positionIt);

    b2World* getWorld();

    ~World();
};


#endif //MICROMACHINES_WORLD_H
