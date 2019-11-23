#include <iostream>
#include "RoomController.h"
#include "Room.h"
#include "Collector.h"
#include "../../Common/Event/LobbySnapshot.h"

#define MAX_AMOUNT_OF_CLIENTS 4

RoomController::RoomController(std::atomic_bool &running) :
            queue(false), acceptSocketRunning(running),
            stopped(false),
            listener(clientsWithNoRoom, running, *this),
            config(new Configuration),
            collector(clientsWithNoRoom, rooms){
    listener.start();
}


int RoomController::addRoom() {
    std::lock_guard<std::mutex> lock(this->m);
    int roomId = roomCounter.returnAndAddOne();
    std::shared_ptr<Room> room(new Room(acceptSocketRunning,
            roomId, MAX_AMOUNT_OF_CLIENTS, config, *this));
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


int RoomController::getIdFromRoom(int clientId) {
    for (auto &room: rooms) {
        if (room.second->hasClient(clientId)) {
            return room.second->getRoomIdFromClient(clientId);
        }
    }
    return -1;
}

void RoomController::moveClientToNewRoom(int newRoomId, int clientId, int newPlayerIdFromRoom){
    int oldRoomId = getRoomIdOfClient(clientId);
    auto client = rooms.at(oldRoomId)->eraseClientAndReturn(clientId);
    client->assignIdFromRoom(newPlayerIdFromRoom);
    rooms.at(newRoomId)->addClientAlreadyCreated(clientId, client);
}


void RoomController::addClientToRoom(int newRoomId, int clientId, int playerIdInRoom) {
    std::lock_guard<std::mutex> lock(this->m);
    std::cout << "Client added to room " << newRoomId << std::endl;
    if (clientsWithNoRoom.count(clientId)) {
        clientsWithNoRoom.at(clientId)->assignIdFromRoom(playerIdInRoom);
        rooms.at(newRoomId)->addClient(clientId, this->clientsWithNoRoom[clientId]);
        this->clientsWithNoRoom.erase(clientId);
    } else {
        moveClientToNewRoom(newRoomId, clientId, playerIdInRoom);
    }
}

void RoomController::addClient(Protocol protocol) {
    std::lock_guard<std::mutex> lock(this->m);
    int clientId = clientCounter.returnAndAddOne();
    std::shared_ptr<ClientThread> client(new ClientThread(std::move(protocol),
            clientId,acceptSocketRunning));
    clientsWithNoRoom.insert({clientId, client});
    client->assignRoomQueue(listener.getReceivingQueue());
    client->start();
    collectDeadClients();
}

void RoomController::addExistentClient(const std::shared_ptr<ClientThread>& client){
    std::lock_guard<std::mutex> lock(this->m);
    int newId = clientCounter.returnAndAddOne();
    client->assignClientId(newId);
    client->restart();
    clientsWithNoRoom.insert({client->getClientId(), client});
    client->assignRoomQueue(listener.getReceivingQueue());
    collectDeadClients();
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
    int playerInRoomId;
    int oldRoomId;
    int oldIdFromRoom;
    switch (input) {
        case ENTER_LOBBY:
            std::cout << "Enter lobby" << std::endl;
            sendToClientsWithoutRoom(snapshot);
            break;
        case ENTER_ROOM:
            client_id = j["client_id"].get<int>();
            roomId = j["selected_room"].get<int>();
            playerInRoomId = j["selected_player"].get<int>();
            std::cout << "Enter to room " << roomId
                      << " from client clientId: " << client_id
                      << " with player id " << playerInRoomId << std::endl;

            oldRoomId = getRoomIdOfClient(client_id);
            oldIdFromRoom = getIdFromRoom(client_id);
            addClientToRoom(roomId, client_id, playerInRoomId);
            snapshot->joinRoom(client_id, roomId);

            snapshot->removeSelectedCar(oldRoomId, oldIdFromRoom);
            snapshot->addSelectedCar(roomId, playerInRoomId);

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
            rooms.at(roomId)->run();
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

void RoomController::eraseRoom(int roomId){
    collector.assignRoomId(roomId);
    collector.start();
    listener.eraseRoomFromSnapshot(roomId);
}


RoomController::~RoomController() {
    std::lock_guard<std::mutex> lock(this->m);
    std::cout << "Borrando controller" << std::endl;

    listener.stop();
    listener.join();
    std::cout << "Destroying clients with no room" << std::endl;

    clientsWithNoRoom.clear();

    std::cout << "Destroying rooms" << std::endl;
    rooms.clear();
}
