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
    std::atomic_bool& acceptSocketRunning;
    std::atomic_bool roomRunning;
    std::unordered_map<int ,std::shared_ptr<ClientThread>> clients;
    SafeQueue<std::shared_ptr<Event>> incomingEvents;
    GameThread game;
    std::vector<int> idsForPlayers;
public:
    Room(std::atomic_bool& acceptSocketRunning, int roomId, int amountOfClients);

    void run() override;

    void addClient(int clientId, std::shared_ptr<ClientThread> newClient);

    void startGame();
    bool isDead();
    void stop();

    std::shared_ptr<Car> createCar(int id, json j);

    ~Room() override;

    bool hasClient(int clientId);
    std::shared_ptr<ClientThread> eraseClientAndReturn(int clientId);

    void sendSnapshotToClients(std::shared_ptr<LobbySnapshot> &snapshot);

    void addClientAlreadyCreated(int clientId,
                            std::shared_ptr<ClientThread> newClient);

    int getAFreeId();

    void joinThread();

    int getRoomIdFromClient(int clientId);

    void addPlayersToJson(json& j);

    void addCarToEachPlayer(const json& j);

    int getColourFromId(int id);
};


#endif //MICROMACHINES_ROOM_H
