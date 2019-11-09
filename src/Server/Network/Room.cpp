//
// Created by alvaro on 29/10/19.
//

#include <iostream>
#include <memory>
#include "Room.h"
#include "../../Common/Event/EventCreator.h"
#include "../../Common/Event/CommandEvent.h"

Room::Room(int roomId, int amountOfPlayers) : roomId(roomId),
        maxAmountOfPlayers(amountOfPlayers),
        running(true),
        incomingEvents(false),
        game(amountOfPlayers, std::make_shared<Configuration>()){
}

void Room::run() {
    std::cout << "Running" << std::endl;
    game.run(running, incomingEvents, clients);
}

bool Room::hasClient(int clientId){
    return this->clients.count(clientId);
}

void Room::addClient(int clientId, const std::shared_ptr<ClientThread>& newClient) {
    if (clients.size() < maxAmountOfPlayers){
        newClient->assignRoomQueue(&incomingEvents);
        newClient->assignCar(std::shared_ptr<Car>(this->game.createCar(clientId)));
        this->clients.insert({clientId, newClient});
    } else {
        throw std::runtime_error("Se intento meter un cliente a una sala llena");
    }

}


void Room::stop() {
    this->running = false;
    for (auto& client: clients){
        client.second->stop();
        client.second->join();
    }
}

Room::~Room() {
    this->stop();
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




