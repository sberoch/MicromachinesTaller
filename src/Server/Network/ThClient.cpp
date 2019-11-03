//
// Created by alvaro on 31/10/19.
//

#include <sstream>
#include <iostream>
#include <utility>
#include "ThClient.h"
#include "../../Common/SocketError.h"


ClientThread::ClientThread(Protocol protocol, RoomController& controller, int clientId,
        std::shared_ptr<Car> car):
            keepTalking(true),
            protocol(std::move(protocol)),
            nonBlockingQueue(false),
            controller(controller),
            id(clientId),
            player(std::ref(protocol), std::move(car)){}


void ClientThread::run() {
    try {
        while (this->keepTalking) {
        try {
            controller.addClientToRoom(1, this->id);

            bool quitMessage = false;
            while (!quitMessage) {
                std::string message = this->protocol.receive();
                this->pushElement(message);
                quitMessage = message == QUIT_STRING;
            }
        } catch (SocketError &e) {
            keepTalking = false;
        }
            keepTalking = false;
        }
    }  catch(const std::exception &e) {
        printf("ERROR from thClient: %s \n", e.what());
    }  catch(...) {
        printf("Unknown error from thclient");
    }
}

std::string ClientThread::popElement(){
    std::string element;
    this->nonBlockingQueue.pop(element);
    return element;
}

void ClientThread::pushElement(const std::string& toBePushed){
    this->nonBlockingQueue.push(toBePushed);
}

//Detiene la ejecucion del cliente y pone la variable booleana en falso
//para que el recolector de clientes muertos pueda reconocerlo como tal.
void ClientThread::stop(){
    protocol.forceShutDown();
    keepTalking = false;
}

//Si el cliente ya produjo el stop o termino de hablar, devuelve true.
bool ClientThread::isDead(){
    return !keepTalking;
}

void ClientThread::sendEvent(std::shared_ptr<Event> event) {
    event->send(this->protocol);
}

void ClientThread::handleInput(const InputEnum &input) {
    this->player.handleInput(input);
}

void ClientThread::sendFromPlayer() {
    this->player.send();
}

