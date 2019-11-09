#ifndef MICROMACHINES_PLAYER_H
#define MICROMACHINES_PLAYER_H

#include "Model/Car/Car.h"
#include "../Common/Socket.h"
#include "../Common/Protocol.h"
#include "../Common/Event/CommandEvent.h"

struct ModifierDTO{
    size_t id;
    size_t type;
    float x;
    float y;
    float angle;
};

class Player {
private:
    Protocol _protocol;
    Car* _car; //TODO move car
    size_t _id;
    ModifierDTO* _modifierDTO;
    bool _modifierToAdd;

public:
    Player(Socket socket, Car* car, size_t id);
    void handleInput(const InputEnum& input);

    void createModifier(const size_t& type, const size_t& id, const float& x, const float& y, const float& angle);

    void receive(std::string& received);
    void send();

    void sendStart(json j); //TODO: mover donde corresponda
};

#endif //MICROMACHINES_PLAYER_H
