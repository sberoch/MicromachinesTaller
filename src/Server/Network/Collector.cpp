//
// Created by alvaro on 12/11/19.
//

#include <unordered_map>
#include <vector>
#include "Collector.h"
#include "Room.h"

Collector::Collector(std::unordered_map<int, std::shared_ptr<ClientThread>>& clients,
                     std::unordered_map<int, std::shared_ptr<Room>>& rooms):
                     clients(clients),
                     rooms(rooms){}

template<class T1, class T2>
void eraseNulls(std::unordered_map<T1, T2>& map) {
    std::vector<T1> idsToEliminate;
    for (auto &actual : map){
        if (actual.second == NULL){
            idsToEliminate.push_back(actual.first);
        }
    }

    for (auto &actualId: idsToEliminate){
        map.erase(actualId);
    }
}

void Collector::collectDeadClients(){
    for (auto &actualClient: clients) {
        if (actualClient.second->isDead()) {
            actualClient.second = nullptr;
        }
    }

    for (auto &actualRoom: rooms) {
        if (actualRoom.second->isDead()) {
            actualRoom.second = nullptr;
        }
    }

    eraseNulls(clients);
    eraseNulls(rooms);
}

Collector::~Collector() = default;
