//
// Created by alvaro on 31/10/19.
//

#include <sstream>
#include <iostream>
#include "ThClient.h"
#include "../../Common/SocketError.h"

//Inicializa la variable atomica booleana y el atendedor de clientes.
//Para este ultimo mueve el socket de la comunicacion.
ClientThread::ClientThread(Protocol protocol, RoomController& controller, int clientId):
            keepTalking(true),
            protocol(std::move(protocol)),
            nonBlockingQueue(),
            controller(controller),
            id(clientId){}

static int toInt(const std::string& string){
    std::stringstream ss(string);
    int x = 0;
    ss >> x;
    return x;
}

int ClientThread::askForRoomId(){
    std::string message = "Ingrese el numero de sala: ";
    protocol.send(message);
    int id = toInt(protocol.receive());
    return id;
}

void ClientThread::run() {
    try {
        while (this->keepTalking) {
        try {
            controller.addClientToRoom(1, this->id);
            protocol.send("Agregado");

            bool quitMessage = false;
            while (!quitMessage) {
                std::string message = this->protocol.receive();
                quitMessage = message == QUIT_STRING;
                if (!quitMessage){
                    std::cout << "Pushing: " << message << std::endl;
                    this->nonBlockingQueue.push(message);
                } else {
                    std::cout << "Quitting" << std::endl;
                }
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

//void ClientThread::sendEvent(){
//    this->nonBlockingQueue.push();
//}

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

