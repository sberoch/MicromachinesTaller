#include <iostream>
#include "RoomController.h"
#include "Room.h"
#include "Collector.h"
#include "../../Common/Event/LobbySnapshot.h"

#define MAX_AMOUNT_OF_CLIENTS 4


RoomController::RoomController(std::atomic_bool &running) :
            queue(false), acceptSocketRunning(running),
            listener(clientsWithNoRoom, running, *this),
            collector(clientsWithNoRoom, rooms){
    listener.start();
}


int RoomController::addRoom() {
    std::lock_guard<std::mutex> lock(this->m);
    int roomId = roomCounter.returnAndAddOne();
    std::shared_ptr<Room> room(new Room(acceptSocketRunning, roomId, MAX_AMOUNT_OF_CLIENTS));
    rooms.insert({roomId, room});
    return roomId;
}

void RoomController::collectDeadClients(){
    collector.collectDeadClients();
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

void RoomController::stop() {
    std::lock_guard<std::mutex> lock(this->m);
    listener.stop();
    listener.join();
    std::cout << "Destroying clients with no room" << std::endl;
    for (auto &client: clientsWithNoRoom){
        client.second->stop();
        client.second->join();
    }

    std::cout << "Destroying rooms" << std::endl;
    for (auto &room: rooms){
        room.second->stop();
        room.second->join();
    }
}

void RoomController::sendToClientsWithoutRoom(std::shared_ptr<LobbySnapshot> snapshot){
    std::lock_guard<std::mutex> lock(this->m);
    for (auto& actualClientWithoutRoom: clientsWithNoRoom){
        actualClientWithoutRoom.second->sendLobbySnapshot(snapshot);
    }
}

void RoomController::sendToAllClientsWithRoom(std::shared_ptr<LobbySnapshot> snapshot){
    std::lock_guard<std::mutex> lock(this->m);
    for (auto& actualRoom: rooms){
        actualRoom.second->sendSnapshotToClients(snapshot);
    }
}

void RoomController::sendToClientsFromRoom(int roomId, std::shared_ptr<LobbySnapshot> snapshot){
    rooms.at(roomId)->sendSnapshotToClients(snapshot);
}

bool RoomController::handleInput(json j, std::shared_ptr<LobbySnapshot> snapshot) {
    bool gameStarted = false;
    Type input = (Type) j["type"].get<int>();
    int client_id;
    int roomId;
    switch (input) {
        case ENTER_LOBBY:
            std::cout << "Enter lobby" << std::endl;
            sendToClientsWithoutRoom(snapshot);
            break;
        case ENTER_ROOM:
            client_id = j["client_id"].get<int>();
            roomId = j["selected_room"].get<int>();
            std::cout << "Enter to room " << roomId << " from client clientId: " << client_id << std::endl;
            this->addClientToRoom(roomId, client_id);
            snapshot->joinRoom(client_id, roomId);
            sendToAllClientsWithRoom(snapshot);
            sendToClientsWithoutRoom(snapshot);
            break;
        case CREATE_ROOM:
            roomId = addRoom();
            std::cout << "Create room with clientId: " << roomId << std::endl;
            snapshot->createRoom(roomId);
            sendToAllClientsWithRoom(snapshot);
            sendToClientsWithoutRoom(snapshot);
            break;
        case PLAY:
            client_id = j["client_id"].get<int>();
            std::cout << "Play from clientId: " << client_id << std::endl;
            roomId = getRoomIdOfClient(client_id);
            snapshot->startGame(roomId);
            sendToClientsWithoutRoom(snapshot);
            sendToAllClientsWithRoom(snapshot);
            rooms.at(roomId)->start();
            gameStarted = true;
            break;
        case COMMAND:
            break;
        case GAME_SNAPSHOT:
            break;
        case LOBBY_SNAPSHOT:
            break;
    }

    return gameStarted;
}


RoomController::~RoomController() {
    if (acceptSocketRunning){
        this->stop();
        acceptSocketRunning = false;
    }
}


