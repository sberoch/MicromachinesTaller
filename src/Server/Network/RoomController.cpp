#include <iostream>
#include "RoomController.h"
#include "Room.h"
#include "../../Common/Event/LobbySnapshot.h"

#define MAX_AMOUNT_OF_CLIENTS 4


RoomController::RoomController(std::atomic_bool &running) :
            queue(false), acceptSocketRunning(running),
            listener(clientsWithNoRoom, running, *this){
    listener.start();
}


int RoomController::addRoom() {
    std::lock_guard<std::mutex> lock(this->m);
    int roomId = roomCounter.returnAndAddOne();
    std::shared_ptr<Room> room(new Room(roomId, MAX_AMOUNT_OF_CLIENTS));
    room->start();
    rooms.insert({roomId, room});
    return roomId;
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

int RoomController::getRoomIdOfClient(int clientId) {
    for (auto &room: rooms) {
        if (room.second->hasClient(clientId)) {
            return room.first;
        }
    }
    return -1;
}

void RoomController::moveClientToNewRoom(int newRoomId, int clientId){
    int oldRoomId = getRoomIdOfClient(clientId);
    auto client = rooms.at(oldRoomId)->eraseClientAndReturn(clientId);
    rooms.at(newRoomId)->addClientAlreadyCreated(clientId, client);
}


void RoomController::addClientToRoom(int roomId, int clientId) {
    std::lock_guard<std::mutex> lock(this->m);
    std::cout << "Client added to room " << roomId << std::endl;

    if (clientsWithNoRoom.count(clientId)) {
        rooms.at(roomId)->addClient(clientId, this->clientsWithNoRoom[clientId]);
        this->clientsWithNoRoom.erase(clientId);
    } else {
        moveClientToNewRoom(roomId, clientId);
    }

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

void RoomController::sendToClientsWithoutRoom(std::shared_ptr<LobbySnapshot> snapshot){
    std::lock_guard<std::mutex> lock(this->m);
    for (auto& actualClientWithoutRoom: clientsWithNoRoom){
        actualClientWithoutRoom.second->sendLobbySnapshot(snapshot);
    }
}

void RoomController::sendToAllClientsWithRoom(std::shared_ptr<LobbySnapshot> snapshot){
    std::lock_guard<std::mutex> lock(this->m);
    int counter = 0;
    for (auto& actualRoom: rooms){
        counter++;
        std::cout << "Counter:" << counter << std::endl;
        actualRoom.second->sendSnapshotToClients(snapshot);
    }
}

void RoomController::sendToClientsFromRoom(int roomId, std::shared_ptr<LobbySnapshot> snapshot){
    rooms.at(roomId)->sendSnapshotToClients(snapshot);
}


bool RoomController::handleInput(json j, std::shared_ptr<LobbySnapshot> snapshot) {
    bool gameStarted = false;
    Type input = (Type) j["type"].get<int>();
    int client_id = -1;
    int roomId;
    switch (input) {
        case ENTER_LOBBY:
            std::cout << "Enter lobby con id: " << client_id << std::endl;
            sendToClientsWithoutRoom(snapshot);
            break;
        case ENTER_ROOM:
            client_id = j["client_id"].get<int>();
            roomId = j["selected_room"].get<int>();
            std::cout << "Enter to room " << roomId << " from client id: " << client_id << std::endl;
            this->addClientToRoom(roomId, client_id);
            snapshot->joinRoom(client_id, roomId);
            sendToAllClientsWithRoom(snapshot);
            sendToClientsWithoutRoom(snapshot);
            break;
        case CREATE_ROOM:
            roomId = addRoom();
            std::cout << "Create room with id: " << roomId << std::endl;
            snapshot->createRoom(roomId);
            sendToAllClientsWithRoom(snapshot);
            sendToClientsWithoutRoom(snapshot);
            break;
        case PLAY:
            client_id = j["client_id"].get<int>();
            std::cout << "Enter room con id: " << client_id << std::endl;
            roomId = getRoomIdOfClient(client_id);
            snapshot->startGame(roomId);
            sendToClientsWithoutRoom(snapshot);
            sendToAllClientsWithRoom(snapshot);
            rooms.at(roomId)->startGame();
            gameStarted = true;
            break;
        case COMMAND:
            std::cout << "Command con id: " << client_id << std::endl;
            break;
        case GAME_SNAPSHOT:
            std::cout << "Snapshot con id: " << client_id << std::endl;
            break;
        case LOBBY_SNAPSHOT:
            break;
    }

    return gameStarted;
}
