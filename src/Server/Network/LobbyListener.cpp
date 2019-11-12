//
// Created by alvaro on 8/11/19.
//

#include "LobbyListener.h"
#include "../../Common/Event/Event.h"
#include "../../Common/Event/CommandEvent.h"
#include "../../Common/SocketError.h"
#include "RoomController.h"
#include "ThClient.h"

LobbyListener::LobbyListener(
        std::unordered_map<int, std::shared_ptr<ClientThread>> &clients,
        std::atomic_bool &running, RoomController& controller): clients(clients),
                                    incomingEvents(false),
                                    running(running),
                                    controller(controller){}

void LobbyListener::run() {
    std::shared_ptr<Event> event;
    std::cout << "Lobby listener started" << std::endl;
    std::shared_ptr<LobbySnapshot> snapshot(new LobbySnapshot);
    while (running) {
        try {
            std::clock_t begin = clock();
            while (incomingEvents.get(event)) {
                controller.handleInput(event->j, snapshot);
            }
            controller.collectDeadClients();
             std::clock_t end = clock();
            double execTime = double(end - begin) / (CLOCKS_PER_SEC / 1000);
            double frames = 25;
            if (execTime < frames) {
                int to_sleep = (frames - execTime);
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(to_sleep));
            }
        } catch (SocketError &se) {
            running = false;
            std::cout << "Lobby listener (SE): " << se.what() << std::endl;
        } catch (std::exception &e){
            running = false;
            std::cout << "Lobby listener (E): " << e.what() << std::endl;
        } catch (...) {
            running = false;
            std::cerr << "Lobby listener: UnknownException.\n";
        }
    }
}

void LobbyListener::collectDeadClients(){
    std::vector<int> idsToBeEliminated;

    for (auto &actualClient: clients) {
        if (actualClient.second->isDead()) {
            actualClient.second->join();
            actualClient.second = nullptr;
            idsToBeEliminated.push_back(actualClient.first);
        }
    }

    for (auto& actualId: idsToBeEliminated){
        clients.erase(actualId);
    }
}

LobbyListener::~LobbyListener() = default;

SafeQueue<std::shared_ptr<Event>>* LobbyListener::getReceivingQueue() {
    return &this->incomingEvents;
}
