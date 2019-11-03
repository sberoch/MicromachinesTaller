//
// Created by alvaro on 30/10/19.
//

#ifndef MICROMACHINES_ROOMCONTROLLER_H
#define MICROMACHINES_ROOMCONTROLLER_H

#include <list>
#include <unordered_map>
#include <atomic>
#include "Thread.h"
#include "../../Common/SafeQueue.h"
#include "SafeCounter.h"

class ClientThread;
class Room;

class RoomController : public Thread {
private:
    std::unordered_map<int, std::shared_ptr<ClientThread>> clientsWithNoRoom;
    std::unordered_map<int, std::shared_ptr<Room>> rooms;
    SafeQueue<std::string> queue;
    SafeCounter roomCounter;
    std::atomic_bool& acceptSocketRunning;
public:
    explicit RoomController(std::atomic_bool& running);

    void run() override;

   void addRoom();

   void addClient(int clientId, const std::shared_ptr<ClientThread>& client);

   void addClientToRoom(int roomId, int clientId);

    bool isDead() override {
        return false;
    }

    void stop() override;

    ~RoomController() override;
};


#endif //MICROMACHINES_ROOMCONTROLLER_H
