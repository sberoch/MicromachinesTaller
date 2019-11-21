//
// Created by alvaro on 8/11/19.
//

#include "LobbyListener.h"
#include "../../Common/Event/Event.h"
#include "../../Common/SocketError.h"
#include "RoomController.h"
#include "ThClient.h"

LobbyListener::LobbyListener(
        std::unordered_map<int, std::shared_ptr<ClientThread>> &clients,
        std::atomic_bool &running, RoomController& controller): clients(clients),
                                    incomingEvents(true),
                                    running(running),
                                    listening(true),
                                    controller(controller){}

void LobbyListener::run() {
    std::shared_ptr<Event> event;
    std::cout << "Lobby listener started" << std::endl;
    std::shared_ptr<LobbySnapshot> snapshot(new LobbySnapshot);
    while (listening && running) {
        try {
            incomingEvents.pop(event);

            if (event != nullptr)
                controller.handleInput(event->j, snapshot);
            else
                listening = false;

            //controller.collectDeadClients();
        } catch (SocketError &se) {
            listening = false;
            std::cout << "Lobby listener (SE): " << se.what() << std::endl;
        } catch (std::exception &e){
            listening = false;
            std::cout << "Lobby listener (E): " << e.what() << std::endl;
        } catch (...) {
            listening = false;
            std::cerr << "Lobby listener: UnknownException.\n";
        }
    }
}

SafeQueue<std::shared_ptr<Event>>* LobbyListener::getReceivingQueue() {
    return &this->incomingEvents;
}

void LobbyListener::stop(){
    listening = false;
    incomingEvents.push(nullptr);
}

LobbyListener::~LobbyListener() = default;
