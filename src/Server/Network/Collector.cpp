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
                     roomIdToErase(-1){}



void Collector::eraseRoom() {
    if (roomIdToErase != -1){
        rooms.at(roomIdToErase) = nullptr;
    } else
        throw std::runtime_error("Se intento eliminar un room con id -1.");
}

void Collector::assignRoomIdToErase(int roomToBeErased){
    this->roomIdToErase = roomToBeErased;
}

void Collector::run() {
    eraseRoom();
}

Collector::~Collector() = default;
