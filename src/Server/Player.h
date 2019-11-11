#ifndef MICROMACHINES_PLAYER_H
#define MICROMACHINES_PLAYER_H

#include "../Common/Socket.h"
#include "../Common/Protocol.h"
#include "../Common/Event/CommandEvent.h"
#include "../Common/Event/SnapshotEvent.h"

class Car;

struct ModifierDTO {
    size_t id;
    size_t type;
    float x;
    float y;
    float angle;
};

struct Effect {
    int type;
    int timeOfAction;
};

class Player {
private:
    std::shared_ptr<Car> _car;
    size_t _id;
    ModifierDTO* _modifierDTO;
    bool _modifierToAdd;

    std::vector<Effect*> _effects;

    void _addEffect(const int& effectType, const int& timeOfAction);


public:
    Player(std::shared_ptr<Car> car, size_t id);
    void handleInput(const InputEnum& input);
    void handleInput(std::string& input);
    void createModifier(const size_t& type, const size_t& id, const float& x, const float& y, const float& angle);
    void receive(std::string& received, Protocol& protocol);
    void modifySnapshot(const std::shared_ptr<SnapshotEvent>& snapshot);

    std::shared_ptr<SnapshotEvent> sendStart(json j);

    void assignCar(std::shared_ptr<Car> newCar);
};

#endif //MICROMACHINES_PLAYER_H
