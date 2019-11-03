//
// Created by alvaro on 29/10/19.
//

#include <iostream>
#include "Room.h"
#include "../../Common/ServerSnapshot.h"

Room::Room() : running(true){}

void Room::run() {
    std::string commands;
    while (running) {
        for (auto &actualClient: clients) {
            std::string popped = actualClient->popElement();
            commands.append(popped);

            std::cout << "Popped: " << popped << std::endl;
        }

        //Hacer algo con los comandos.
//        if (!commands.empty()){
//            std::cout << "All commands: " << commands << std::endl;
//            commands.clear();
//        }
    }
}

void Room::addClient(const std::shared_ptr<ClientThread>& newClient) {
    this->clients.push_back(newClient);
}


bool Room::isDead() {
    return !running;
}


void Room::stop() {
    this->running = false;
    for (auto& client: clients){
        client->stop();
        client->join();
    }
}

Room::~Room() {
    this->stop();
}




