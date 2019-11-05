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
    int _id;

public:
    Player(Socket socket, Car* car, int id);
    void handleInput(const InputEnum& input);
    void handleInput(std::string& input);
    void receive(std::string& received);
    void send();

    void sendStart(json j); //TODO: mover donde corresponda

};

#endif //MICROMACHINES_PLAYER_H
