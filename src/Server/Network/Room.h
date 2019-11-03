//
// Created by alvaro on 29/10/19.
//

#ifndef MICROMACHINES_ROOM_H
#define MICROMACHINES_ROOM_H


#include <vector>
#include <memory>
#include "ThClient.h"
#include "../../Common/Thread.h"
#include "../Model/Game.h"

class Room: public Thread{
private:
    std::vector<std::shared_ptr<ClientThread>> clients;
    std::atomic<bool> running;
    Game game;
public:
    explicit Room(int amountOfClients);

    void run() override;

    void addClient(const std::shared_ptr<ClientThread>& newClient);

    void stop();

    std::shared_ptr<Car> createCar(int id);

    ~Room() override;
};


#endif //MICROMACHINES_ROOM_H
