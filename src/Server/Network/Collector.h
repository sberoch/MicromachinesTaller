//
// Created by alvaro on 12/11/19.
//

#ifndef MICROMACHINES_COLLECTOR_H
#define MICROMACHINES_COLLECTOR_H


#include <memory>

class ClientThread;
class Room;

class Collector {
private:
    std::unordered_map<int, std::shared_ptr<ClientThread>>& clients;
    std::unordered_map<int, std::shared_ptr<Room>>& rooms;
public:
    Collector(std::unordered_map<int, std::shared_ptr<ClientThread>>& clients,
              std::unordered_map<int, std::shared_ptr<Room>>& rooms);

    void collectDeadClients();

    ~Collector();
};


#endif //MICROMACHINES_COLLECTOR_H
