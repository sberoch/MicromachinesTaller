
#ifndef MICROMACHINES_WORLD_H
#define MICROMACHINES_WORLD_H

#define DEGTORAD 0.0174532925199432957f

#include "../json/json.hpp"
#include <Box2D/Box2D.h>
#include "Car/Car.h"
#include "ContactListener.h"
#include "Track.h"
#include "FixtureUserData.h"
#include "Grass.h"
#include "Modifier.h"

using json = nlohmann::json;


class World {
private:
    b2World* _world;
    float _timeStep;
    std::shared_ptr<Configuration> _configuration;

    int _n_of_cars;
    //TODO use shared pointers
    std::vector<Car*> _cars;
    void _getCarConfigData(size_t id, float& x, float& y, float& angle);
    std::vector<Track*> _track;
    std::vector<Grass*> _grass;

    //A vector of active modifiers to delete
    std::vector<Modifier*> _activeModifiers;
    std::vector<int> _modifierType;
    size_t _maxId;

    //Floor
    b2BodyDef _track_body_def;
    ContactListener* _contactListener;

    void _removeGrabbedModifiers();
    void _updateCarsOnGrass();

public:
    World(size_t n_of_cars, std::shared_ptr<Configuration> configuration);

    json getSerializedMap();

    void createTrack(std::vector<Track*>& track);
    void createGrass(std::vector<Grass*>& grass);
    Car* createCar(size_t id); //TODO move

    //Modifiers
    void createRandomModifier(size_t& type, size_t& id, float& x, float& y, float& angle);

    void step(uint32_t velocityIt, uint32_t positionIt);

    b2World* getWorld();

    ~World();
};


#endif //MICROMACHINES_WORLD_H