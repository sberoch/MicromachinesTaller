//
// Created by alvaro on 12/11/19.
//

#include <unordered_map>
#include <vector>
#include "Collector.h"
#include "Room.h"

Collector::Collector(std::unordered_map<int, std::shared_ptr<ClientThread>>& clients,
                     std::map<int, std::shared_ptr<Room>>& rooms):
                     clients(clients),
                     rooms(rooms),
                     clientId(-1),
                     roomId(-1){}


void Collector::collectDeadRooms(){
    for (auto &actualRoom: rooms) {
        if (actualRoom.second->isDead()) {
            actualRoom.second = nullptr;
        }
    }
}

void Collector::eraseRoom() {
    if (roomId != -1){
        rooms.at(roomId) = nullptr;
    } else
        throw std::runtime_error("Se intento eliminar un room con id -1.");
}

void Collector::assignRoomId(int roomId){
    this->roomId = roomId;
}

void Collector::run() {
    eraseRoom();
}

Collector::~Collector() = default;
