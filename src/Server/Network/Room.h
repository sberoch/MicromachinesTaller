//
// Created by alvaro on 29/10/19.
//

#ifndef MICROMACHINES_ROOM_H
#define MICROMACHINES_ROOM_H


#include <vector>
#include <memory>
#include "ThClient.h"
#include "../../Common/Thread.h"
#include "../Model/GameThread.h"

class Room: public Thread{
private:
    int roomId;
    int maxAmountOfPlayers;
    std::atomic<bool> running;
    std::unordered_map<int ,std::shared_ptr<ClientThread>> clients;
    SafeQueue<std::shared_ptr<Event>> incomingEvents;
    GameThread game;
public:
    explicit Room(int roomId, int amountOfClients);

    void run() override;

    void addClient(int clientId, const std::shared_ptr<ClientThread>& newClient);

    void stop();

    std::shared_ptr<Car> createCar(int id);

    ~Room() override;

    bool hasClient(int clientId);
    std::shared_ptr<ClientThread> eraseClientAndReturn(int clientId);
};


#endif //MICROMACHINES_ROOM_H
