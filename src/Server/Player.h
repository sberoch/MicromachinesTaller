#ifndef MICROMACHINES_PLAYER_H
#define MICROMACHINES_PLAYER_H

#include "Model/Car/Car.h"
#include "../Common/Socket.h"
#include "../Common/Protocol.h"
#include "../Common/Event/CommandEvent.h"
#include "../Common/Event/SnapshotEvent.h"

class Player {
private:
    std::shared_ptr<Car> _car;
    size_t _id;

public:
    Player(std::shared_ptr<Car> car, size_t id);
    void handleInput(const InputEnum& input);
    void handleInput(std::string& input);
    void receive(std::string& received, Protocol& protocol);
    std::shared_ptr<SnapshotEvent> makeSnapshot();

    std::shared_ptr<SnapshotEvent> sendStart(json j);

    void assignCar(std::shared_ptr<Car> newCar);
};

#endif //MICROMACHINES_PLAYER_H
