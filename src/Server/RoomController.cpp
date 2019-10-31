//
// Created by alvaro on 30/10/19.
//

#include "RoomController.h"

RoomController::RoomController() : queue(false) {
    //Crea un room, luego se deberan agregar clientes.
    std::shared_ptr<Room> newRoom(new Room());
    addRoom(1, newRoom);
}

void RoomController::run() {
    std::string commands;
    for (auto& waitingClient: clientsWithNoRoom){
        std::string popped = waitingClient->popElement();
        commands.append(popped);
        std::cout << "Popped: " << popped << std::endl;
    }

    //Hacer algo con los comandos.
    std::cout << "All commands: " << commands << std::endl;
}

RoomController::~RoomController() {
    std::cout << "Destroying clients with no room" << std::endl;
    for (auto &client: clientsWithNoRoom){
        client->stop();
        client->join();
    }
}

void RoomController::addRoom(int roomId, std::shared_ptr<Room> room) {
    rooms.insert({roomId, room});
}

void RoomController::addClientToRoom(int roomId,
                                const std::shared_ptr<ClientThread>& client) {
    rooms[roomId]->addClient(client);
}

void RoomController::addClient(const std::shared_ptr<ClientThread>& client) {
    this->clientsWithNoRoom.push_back(client);
    client->start();

    for (auto &actualClient: clientsWithNoRoom) {
        if (actualClient->isDead()) {
            actualClient->join();
            actualClient = nullptr;
        }
    }
    clientsWithNoRoom.remove(nullptr);
}


