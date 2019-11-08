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
                                    running(running),
                                    controller(controller){
    this->incomingEvents = new SafeQueue<std::shared_ptr<Event>>(false);
}

void LobbyListener::run() {
    std::shared_ptr<Event> event;
    std::cout << "Lobby listener started" << std::endl;
    while (running) {
        try {
            if (!clients.empty()) {
                while (incomingEvents->get(event)) {
                    //clients[event->j["client_id"]]->handleInput((InputEnum) event->j["cmd_id"].get<int>());
                    controller.handleInput(event->j);
                }

//                for (auto &actualClient : clients) {
//                    actualClient.second->sendSnapshot();
//                }
            }
        } catch (SocketError &se) {
            running = false;
            std::cout << "Lobby listener: " << se.what() << std::endl;
        } catch (...) {
            running = false;
            std::cerr << "Lobby listener: UnknownException.\n";
        }
    }
}

void LobbyListener::createRoom(){
    this->controller.addRoom();
}

LobbyListener::~LobbyListener() {
    delete(this->incomingEvents);
}

SafeQueue<std::shared_ptr<Event>>* LobbyListener::getReceivingQueue() {
    return this->incomingEvents;
}
