//
// Created by alvaro on 31/10/19.
//

#include <sstream>
#include <iostream>
#include <utility>
#include "ThClient.h"
#include "../../Common/SocketError.h"
#include "../../Common/Event/EventCreator.h"


ClientThread::ClientThread(Protocol protocol, RoomController& controller, int clientId,
        std::shared_ptr<Car> car):
            keepTalking(true),
            protocol(std::move(protocol)),
            controller(controller),
            id(clientId),
            player(std::ref(protocol), std::move(car)),
            receivingNonBlockingQueue(true),
            sendingBlockingQueue(true),
            sender(this->protocol, sendingBlockingQueue,
                   reinterpret_cast<bool &>(keepTalking)),
            receiver(this->protocol, receivingNonBlockingQueue,
                     reinterpret_cast<bool &>(keepTalking)){}


void ClientThread::run() {
    try {
        try {
            controller.addClientToRoom(1, this->id);
            this->sender.start();
            this->receiver.start();
        } catch (SocketError &e) {
            keepTalking = false;
        }
            keepTalking = false;
    } catch(const std::exception &e) {
        printf("ERROR from thClient: %s \n", e.what());
    } catch(...) {
        printf("Unknown error from thclient");
    }
}

//Detiene la ejecucion del cliente y pone la variable booleana en falso
//para que el recolector de clientes muertos pueda reconocerlo como tal.
void ClientThread::stop(){
    protocol.forceShutDown();
    sender.join();
    receiver.join();
    keepTalking = false;
}

//Si el cliente ya produjo el stop o termino de hablar, devuelve true.
bool ClientThread::isDead(){
    return !keepTalking;
}

void ClientThread::sendEvent(const std::shared_ptr<Event>& event) {
    event->send(this->protocol);
}

void ClientThread::handleInput(const InputEnum &input) {
    this->player.handleInput(input);
}

void ClientThread::sendFromPlayer() {
    this->player.send();
}

std::shared_ptr<Event> ClientThread::popFromNonBlockingQueue() {
    std::shared_ptr<Event> event;
    this->receivingNonBlockingQueue.pop(event);
    return event;
}

