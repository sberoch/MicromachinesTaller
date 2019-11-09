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
            if (!clients.empty()) {
                while (incomingEvents.get(event)) {
                    controller.handleInput(event->j, snapshot);
                }

                //newClient->sendStart(game.getSerializedMap())
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

void LobbyListener::createRoom(){
    this->controller.addRoom();
}

LobbyListener::~LobbyListener() = default;

SafeQueue<std::shared_ptr<Event>>* LobbyListener::getReceivingQueue() {
    return &this->incomingEvents;
}
