//
// Created by alvaro on 29/10/19.
//

#include <iostream>
#include <memory>
#include "Room.h"
#include "../../Common/ServerSnapshot.h"
#include "../../Common/Event/EventCreator.h"
#include "../../Common/InputEnum.h"
#include "../../Common/Event/CommandEvent.h"

Room::Room(int amountOfPlayers) : running(true),
        incomingEvents(false),
        game(amountOfPlayers, std::make_shared<Configuration>()){
}

void Room::run() {
    std::cout << "Running" << std::endl;
    while (running){
        std::clock_t begin = clock();

        std::shared_ptr<Event> event;
        while (incomingEvents.get(event)){
            //clients[event->j["client_id"]]->handleInput((InputEnum) event->j["cmd_id"].get<int>());
            clients.at(0)->handleInput((InputEnum) event->j["cmd_id"].get<int>());
        }
        game.step();

        for (auto &actualClient : clients){
            //actualClient->sen(event);
            actualClient.second->sendFromPlayer();
        }

        std::clock_t end = clock();
        double execTime = double(end - begin) / (CLOCKS_PER_SEC / 1000);
        double frames = 25;
        if (execTime < frames) {
            int to_sleep = (frames - execTime);
            std::this_thread::sleep_for(std::chrono::milliseconds(to_sleep));
        }
    }
}

void Room::addClient(int clientId, const std::shared_ptr<ClientThread>& newClient) {
    newClient->assignRoomQueue(&incomingEvents);
    this->clients.insert({clientId, newClient});
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




