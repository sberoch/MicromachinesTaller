#ifndef MICROMACHINES_PLAYER_H
#define MICROMACHINES_PLAYER_H

#include "Model/Car/Car.h"
#include "../Common/Socket.h"
#include "../Common/Protocol.h"
#include "../Common/InputEnum.h"
#include "../Common/Event/CommandEvent.h"

class Player {
private:
    Protocol& _protocol;
    std::shared_ptr<Car> _car; //TODO move car

public:
    Player(Protocol& protocol, std::shared_ptr<Car> car);
    Player(Socket socket, std::shared_ptr<Car> car);
    void handleInput(const InputEnum& input);
    void handleInput(std::string& input);
    void receive(std::string& received);
    void send();

};

#endif //MICROMACHINES_PLAYER_H
