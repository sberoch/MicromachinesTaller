//
// Created by alvaro on 12/11/19.
//

#ifndef MICROMACHINES_COLLECTOR_H
#define MICROMACHINES_COLLECTOR_H


#include <memory>
#include <map>
#include "../../Common/Thread.h"

class ClientThread;
class Room;

class Collector : public Thread {
private:
    std::unordered_map<int, std::shared_ptr<ClientThread>>& clients;
    std::map<int, std::shared_ptr<Room>>& rooms;
    int clientId;
    int roomIdToErase;
public:
    Collector(std::unordered_map<int, std::shared_ptr<ClientThread>>& clients,
              std::map<int, std::shared_ptr<Room>>& rooms);

    void run() override;

    void eraseRoom();
    void assignRoomIdToErase(int roomToBeErased);

    ~Collector() override;
};


#endif //MICROMACHINES_COLLECTOR_H
