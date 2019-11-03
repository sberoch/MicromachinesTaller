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

std::shared_ptr<Car> createCar(int id){
    std::shared_ptr<Room> room(new Room(0));
    return room->createCar(id);
}

void RoomController::addRoom() {
    //HARDCODEADO
    int amountOfClients = 4;
    std::shared_ptr<Room> room(new Room(amountOfClients));
    room->start();
    int roomId = roomCounter.addOneAndReturn();
    rooms.insert({roomId, room});
}

void RoomController::addClientToRoom(int roomId, int clientId) {
    std::cout << "Client added to room " << roomId << std::endl;
    rooms[roomId]->addClient(this->clientsWithNoRoom[clientId]);
    this->clientsWithNoRoom.erase(clientId);
}

void RoomController::addClient(int clientId, Protocol protocol) {
    std::shared_ptr<Car> car(createCar(clientId));
    std::shared_ptr<ClientThread> client(new ClientThread(std::move(protocol), *this, clientId, car));
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
