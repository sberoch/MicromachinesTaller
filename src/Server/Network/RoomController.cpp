//
// Created by alvaro on 30/10/19.
//

#include <iostream>
#include "RoomController.h"
#include "Room.h"

RoomController::RoomController(std::atomic_bool &running) :
            queue(false), acceptSocketRunning(running) {
    addRoom();
}

void RoomController::run() {
//    std::string commands;
//    while (acceptSocketRunning) {
//        for (auto &waitingClient: clientsWithNoRoom) {
//            std::string popped = waitingClient.second->popElement();
//            commands.append(popped);
//
//            std::cout << "Popped: " << popped << std::endl;
//        }
//
//        //Hacer algo con los comandos.
//        if (!commands.empty()){
//            std::cout << "All commands: " << commands << std::endl;
//            commands.clear();
//        }
//    }
}

void RoomController::addRoom() {
    std::shared_ptr<Room> room(new Room());
    room->start();
    int roomId = roomCounter.addOneAndReturn();
    rooms.insert({roomId, room});
}

void RoomController::addClientToRoom(int roomId, int clientId) {
    std::cout << "Client added to room" << roomId << std::endl;
    rooms[roomId]->addClient(this->clientsWithNoRoom[clientId]);
    this->clientsWithNoRoom.erase(clientId);
}

void RoomController::addClient(int clientId, const std::shared_ptr<ClientThread>& client) {
    clientsWithNoRoom.insert({clientId, client});
    client->start();

    std::vector<int> idsToBeEliminated;

    for (auto &actualClient: clientsWithNoRoom) {
        if (actualClient.second->isDead()) {
            actualClient.second->join();
            actualClient.second = nullptr;
            idsToBeEliminated.push_back(actualClient.first);
        }
    }

    for (auto& actualId: idsToBeEliminated){
        clientsWithNoRoom.erase(actualId);
    }
}


RoomController::~RoomController() {
    this->stop();
}

void RoomController::stop() {
    std::cout << "Destroying clients with no room" << std::endl;
    for (auto &client: clientsWithNoRoom){
        client.second->stop();
        client.second->join();
    }

    clientsWithNoRoom.clear();

    std::cout << "Destroying rooms" << std::endl;
    for (auto &room: rooms){
        room.second->stop();
        room.second->join();
    }

    rooms.clear();
}
