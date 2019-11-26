//
// Created by alvaro on 30/9/19.
//

#ifndef HONEYPOT_SERVERTHCLIENT_H
#define HONEYPOT_SERVERTHCLIENT_H


#include <atomic>
#include <iostream>
#include "RoomController.h"
#include "../../Common/Protocol.h"
#include "../../Common/Event/Event.h"
#include "../Player.h"
#include "EventReceiver.h"
#include "EventSender.h"
#include "../../Common/Event/EndSnapshot.h"

#define QUIT_STRING "QUIT"

class ClientThread {
private:
    std::atomic<bool> keepTalking;
    Protocol protocol;
    int clientId;
    int idFromRoom;
    int numberOfLaps;
    Player player;
    SafeQueue<std::shared_ptr<Event>>* receivingNonBlockingQueue;
    SafeQueue<std::shared_ptr<Event>> sendingBlockingQueue;
    EventReceiver receiver;
    EventSender sender;

    void stop();
public:
    ClientThread(Protocol protocol, int clientId, std::atomic_bool& acceptSocketRunning);

    void run();
    bool isDead();

    void handleEvent(const std::shared_ptr<Event>& event);
    void sendSnapshot(const std::shared_ptr<SnapshotEvent>& snapshot);
    void sendStart(json j);

    void assignClientId(int newId);
    void assignRoomQueue(SafeQueue<std::shared_ptr<Event>>* receiveingQueue);
    void assignCar(const std::shared_ptr<Car>& car);
    void assignIdFromRoom(int newIdFromRoom);

    int getClientId();
    int getNumberOfLaps();
    int getIdFromRoom();

    void sendLobbySnapshot(std::shared_ptr<LobbySnapshot>& snapshot);
    void modifySnapshotFromClient(const std::shared_ptr<SnapshotEvent> &snapshot);
    void createModifier(const size_t& type, const size_t& id, const float& x,
            const float& y, const float& angle);

    bool update();
    bool finishedPlaying();

    void sendEndEvent(const std::shared_ptr<EndSnapshot> &endSnapshot);
    void restart();

    ~ClientThread();
};




#endif //HONEYPOT_SERVERTHCLIENT_H
