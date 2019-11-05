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
        incomingEvents(true),
        game(amountOfPlayers, std::make_shared<Configuration>()){
}

void Room::run() {
    std::cout << "Running" << std::endl;
    
    while (running){
        std::clock_t begin = clock();
        for (auto& client: clients){
            this->incomingEvents.push(client->popFromNonBlockingQueue());
            std::shared_ptr<Event> event;
            incomingEvents.pop(event);

            client->handleInput((InputEnum) event->j["cmd_id"].get<int>());
            game.step();

            for (auto& actualClient : clients){
                actualClient->sendEvent(event);
            }
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

void Room::addClient(const std::shared_ptr<ClientThread>& newClient) {
    this->clients.push_back(newClient);
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

std::shared_ptr<Car> Room::createCar(int id) {
    std::shared_ptr<Car> car(game.createCar(id));
    return car;
}




