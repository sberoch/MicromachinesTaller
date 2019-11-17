#ifndef MICROMACHINES_WORLD_H
#define MICROMACHINES_WORLD_H

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
    std::vector<Car*> _cars;
    void _getCarConfigData(size_t id, float& x, float& y, float& angle);
    std::vector<std::shared_ptr<Track>> _track;
    std::vector<std::shared_ptr<Grass>> _grass;

    //A vector of active modifiers to delete
    std::vector<Modifier*> _activeModifiers;
    std::vector<int> _modifierType;
    size_t _maxId;

    ContactListener* _contactListener;

    void _removeGrabbedModifiers();
    void _updateCarsOnGrass();

public:
    World(size_t n_of_cars, std::shared_ptr<Configuration> configuration);

    json getSerializedMap();

    void createTrack();
    void createGrass();
    Car* createCar(size_t id);

    //Modifiers
    void createRandomModifier(size_t& type, size_t& id, float& x, float& y, float& angle);

    void step(uint32_t velocityIt, uint32_t positionIt);

    ~World();
};


#endif //MICROMACHINES_WORLD_H