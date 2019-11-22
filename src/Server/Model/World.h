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
#include "../mods/DTOs.h"
#include "DestructionListener.h"

using json = nlohmann::json;

class World {
private:
    std::shared_ptr<b2World> _world;
    float _timeStep;
    std::shared_ptr<Configuration> _configuration;

    int _n_of_cars;
    std::vector<std::shared_ptr<Car>> _cars;

    std::vector<std::shared_ptr<Track>> _track;
    std::vector<std::shared_ptr<Grass>> _grass;

    //A vector of active modifiers to delete
    std::vector<std::shared_ptr<Modifier>> _activeModifiers;
    std::vector<int> _modifierType;
    size_t _maxId;

    std::shared_ptr<ContactListener> _contactListener;

    void _removeGrabbedModifiers();
    void _updateCarsOnGrass();

    b2World* _world;

public:
    World(size_t n_of_cars, const std::shared_ptr<Configuration>& configuration);

    json getSerializedMap();


    void createTrack();
    void createGrass();
    std::shared_ptr<Car> createCar(size_t id, json cars);

    //Modifiers
    void createRandomModifier(size_t& type, size_t& id, float& x, float& y, float& angle);

    void step(uint32_t velocityIt, uint32_t positionIt);

    void toDTO(WorldDTO_t* world);
    void dtoToModel(WorldDTO_t* worldDTO);

    ~World();

    json getCarById(int id, json j);
};


#endif //MICROMACHINES_WORLD_H