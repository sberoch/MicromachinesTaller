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
                     rooms(rooms),
                     clientId(-1),
                     roomId(-1){}

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

void Collector::eraseRoom() {
    if (roomId != -1)
        rooms.erase(roomId);
    else
        throw std::runtime_error("Se intento eliminar un room con id -1.");
}

void Collector::assignRoomId(int roomId){
    this->roomId = roomId;
}

void Collector::run() {
    eraseRoom();
}

Collector::~Collector() = default;
