//
// Created by alvaro on 29/10/19.
//

#include <iostream>
#include <memory>
#include "Room.h"
#include "../../Common/Event/EventCreator.h"
#include "../../Common/Event/CommandEvent.h"
#include "../../Common/SocketError.h"

Room::Room(std::atomic_bool& acceptSocketRunning,
        int roomId, int amountOfPlayers) : roomId(roomId),
                                              maxAmountOfPlayers(amountOfPlayers),
                                              acceptSocketRunning(acceptSocketRunning),
                                              roomRunning(true),
                                              incomingEvents(false),
                                              game(amountOfPlayers, std::make_shared<Configuration>()){
}

void Room::run() {
    try{
    std::cout << "Running" << std::endl;
    startGame();
    game.run(acceptSocketRunning,roomRunning, incomingEvents, clients);

    } catch (SocketError &se) {
        roomRunning = false;
        std::cout << "Room id: " << roomId << " (SE): " << se.what() << std::endl;
    } catch (std::exception &e){
        roomRunning = false;
        std::cout << "Room id: " << roomId << " (E): " << e.what() << std::endl;
    } catch (...) {
        roomRunning = false;
        std::cout << "Room id: " << roomId << " unknown exception" << std::endl;
    }
}

bool Room::hasClient(int clientId){
    return this->clients.count(clientId);
}

void Room::addClientAlreadyCreated(int clientId, std::shared_ptr<ClientThread> newClient) {
    if (clients.size() < maxAmountOfPlayers){
        this->clients.insert({clientId, newClient});
    } else {
        throw std::runtime_error("Se intento meter un cliente a una sala llena");
    }
}

void Room::addClient(int clientId, std::shared_ptr<ClientThread> newClient) {
    if (clients.size() < maxAmountOfPlayers){
        // Usar id propia del room
        newClient->assignCar(std::shared_ptr<Car>(this->game.createCar(clientId)));
        this->clients.insert({clientId, newClient});
    } else {
        throw std::runtime_error("Se intento meter un cliente a una sala llena");
    }
}



std::shared_ptr<Car> Room::createCar(int id) {
    std::shared_ptr<Car> car(game.createCar(id));
    return car;
}

std::shared_ptr<ClientThread> Room::eraseClientAndReturn(int clientId) {
    std::shared_ptr<ClientThread> client = this->clients.at(clientId);
    this->clients.erase(clientId);
    return client;
}

void Room::sendSnapshotToClients(std::shared_ptr<LobbySnapshot>& snapshot){
    for (auto& client: clients){
        client.second->sendLobbySnapshot(snapshot);
    }
}

void Room::startGame() {
    for (auto& client: clients){
        client.second->assignRoomQueue(&incomingEvents);
        client.second->sendStart(game.getSerializedMap());
    }
    game.startGame();
}

bool Room::isDead() {
    return !roomRunning;
}


void Room::stop() {
    this->roomRunning = false;
    for (auto& client: clients){
        if (!client.second->isDead()){
            client.second->stop();
            client.second->join();
        }
    }
}

Room::~Room() {
    this->stop();
}



