//
// Created by alvaro on 8/11/19.
//

#ifndef MICROMACHINES_LOBBYLISTENER_H
#define MICROMACHINES_LOBBYLISTENER_H


#include <atomic>
#include "../../Common/Thread.h"
#include "../../Common/SafeQueue.h"
#include "../../Common/Event/Event.h"

class RoomController;
class ClientThread;

class LobbyListener : public Thread{
private:
    std::unordered_map<int, std::shared_ptr<ClientThread>>& clients;
    SafeQueue<std::shared_ptr<Event>> incomingEvents;
    std::atomic_bool& running;
    std::atomic_bool listening;
    RoomController& controller;

public:
    LobbyListener(std::unordered_map<int, std::shared_ptr<ClientThread>>& clientsWithNoRoom,
                    std::atomic_bool& running, RoomController& controller);

    void run() override;

    void createRoom();
    ~LobbyListener() override;

    SafeQueue<std::shared_ptr<Event>>* getReceivingQueue();

    void collectDeadClients();

    void stop();
};


#endif //MICROMACHINES_LOBBYLISTENER_H
