#ifndef MICROMACHINES_PLAYER_H
#define MICROMACHINES_PLAYER_H

#include "../Common/Socket.h"
#include "../Common/Protocol.h"
#include "../Common/Event/CommandEvent.h"
#include "../Common/Event/SnapshotEvent.h"
#include "../mods/DTOs.h"

class Car;

struct Effect {
    int type;
    int timeOfAction;
};

class Player {
private:
    std::shared_ptr<Car> _car;
    int& inRoomId;
    ModifierDTO_t _modifierDTO;
    bool _modifierToAdd;

    std::vector<Effect*> _effects;
    bool done;

    void _addEffect(const int& effectType, const int& timeOfAction);


public:
    Player(std::shared_ptr<Car> car, int& inRoomId);
    void handleInput(const InputEnum& input);
    void handleInput(std::string& input);
    void createModifier(const size_t& type, const size_t& id, const float& x, const float& y, const float& angle);
    void receive(std::string& received, Protocol& protocol);
    void modifySnapshot(const std::shared_ptr<SnapshotEvent>& snapshot);

    std::shared_ptr<SnapshotEvent> sendStart(json j);

    void assignCarAndId(std::shared_ptr<Car> newCar);

    void assignCarId(int id);

    int update();

    bool finishedPlaying();
};

#endif //MICROMACHINES_PLAYER_H
