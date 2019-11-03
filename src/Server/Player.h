#ifndef MICROMACHINES_PLAYER_H
#define MICROMACHINES_PLAYER_H

#include "Model/Car/Car.h"
#include "../Common/Socket.h"
#include "../Common/Protocol.h"
#include "../Common/Event/CommandEvent.h"

class Player {
private:
    Protocol _protocol;
    Car* _car; //TODO move car
    size_t _id;

public:
    Player(Socket socket, Car* car, size_t id);
    void handleInput(const InputEnum& input);
    void receive(std::string& received);
    void send();

};

#endif //MICROMACHINES_PLAYER_H
