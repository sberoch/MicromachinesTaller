#include <iostream>
#include "RoomController.h"
#include "Room.h"
#define MAX_AMOUNT_OF_CLIENTS 4


RoomController::RoomController(std::atomic_bool &running) :
            queue(false), acceptSocketRunning(running),
            listener(clientsWithNoRoom, running, *this){
    listener.start();
}


void RoomController::addRoom() {
    std::lock_guard<std::mutex> lock(this->m);
    int roomId = roomCounter.returnAndAddOne();
    std::shared_ptr<Room> room(new Room(roomId, MAX_AMOUNT_OF_CLIENTS));
    room->start();
    rooms.insert({roomId, room});
}

void RoomController::collectDeadClients(){
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

void RoomController::addClientToRoom(int roomId, int clientId) {
    std::lock_guard<std::mutex> lock(this->m);
    std::cout << "Client added to room " << roomId << std::endl;
    rooms[roomId]->addClient(clientId, this->clientsWithNoRoom[clientId]);
    this->clientsWithNoRoom.erase(clientId);
}

void RoomController::addClient(int clientId, Protocol protocol) {
    std::lock_guard<std::mutex> lock(this->m);
    std::shared_ptr<ClientThread> client(new ClientThread(std::move(protocol),
            *this, clientId,acceptSocketRunning));
    clientsWithNoRoom.insert({clientId, client});
    client->assignRoomQueue(listener.getReceivingQueue());
    client->start();
    collectDeadClients();
}


RoomController::~RoomController() {
    this->stop();
}

void RoomController::stop() {
    std::lock_guard<std::mutex> lock(this->m);
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


void RoomController::handleInput(json j) {
    Type input = (Type) j["type"].get<int>();
    int client_id = -1;
    switch (input) {
        case ENTER_LOBBY:
            std::cout << "Enter lobby con id: " << client_id << std::endl;
            break;
        case PLAY_AS_USER:
            client_id = j["client_id"].get<int>();
            std::cout << "Play as user con id: " << client_id << std::endl;
            break;
        case PLAY_AS_BOT:
            client_id = j["client_id"].get<int>();
            std::cout << "Play as bot con id: " << client_id << std::endl;
            break;
        case ENTER_ROOM:
            client_id = j["client_id"].get<int>();
            std::cout << "Enter room con id: " << client_id << std::endl;
            break;
        case CREATE_ROOM:
            std::cout << "Enter room con id: " << client_id << std::endl;
            break;
        case PLAY:
            std::cout << "Enter room con id: " << client_id << std::endl;
            break;
        case COMMAND:
            std::cout << "Command con id: " << client_id << std::endl;
            break;
        case SNAPSHOT:
            std::cout << "Snapshot con id: " << client_id << std::endl;
            break;
    }
}
