//
// Created by alvaro on 30/10/19.
//

#ifndef MICROMACHINES_ROOMCONTROLLER_H
#define MICROMACHINES_ROOMCONTROLLER_H


#include "Room.h"
#include <list>

class RoomController : public Thread {
private:
    std::list<std::shared_ptr<ClientThread>> clientsWithNoRoom;
    std::unordered_map<int, std::shared_ptr<Room>> rooms;
    SafeQueue<std::string> queue;
public:
    RoomController();

    void run() override;

   void addRoom(int roomId, std::shared_ptr<Room> room);

   void addClient(const std::shared_ptr<ClientThread>& client);

   void addClientToRoom(int roomId, const std::shared_ptr<ClientThread>& client);

    bool isDead() override {
        return false;
    }

    void stop() override {}

    ~RoomController() override;
};


#endif //MICROMACHINES_ROOMCONTROLLER_H
