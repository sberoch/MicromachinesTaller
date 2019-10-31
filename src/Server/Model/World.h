#ifndef MICROMACHINES_WORLD_H
#define MICROMACHINES_WORLD_H

#define DEGTORAD 0.0174532925199432957f

#include <Box2D/Box2D.h>
#include "Car/Car.h"
#include "ContactListener.h"
#include "Car/Tire.h"
#include "Track.h"

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

    void _tire_vs_groundArea(b2Fixture* tireFixture, b2Fixture* groundAreaFixture, bool began);

public:
    World(size_t n_of_cars, std::shared_ptr<Configuration> configuration);

    std::vector<Track*> createTrack();
    Car* createCar(size_t id);
    Tire* createTire(); //Desp con move

    void step(uint32_t velocityIt, uint32_t positionIt);

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void handleContact(b2Contact* contact, bool began);

    b2World* getWorld();

    ~World();
};


#endif //MICROMACHINES_WORLD_H
