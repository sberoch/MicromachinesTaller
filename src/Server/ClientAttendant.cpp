//
// Created by alvaro on 28/9/19.
//

#include <functional>
#include <vector>
#include <iostream>
#include "ClientAttendant.h"
#define KEY_POSITION 0
#define SPACE_CHAR ' '
#define QUIT_STRING "QUIT"


ClientAttendant::ClientAttendant(Socket skt) : protocol(std::move(skt)){}


void ClientAttendant::receivingLoop() {
    std::string bienvenida = "Bienvenido";
    protocol.send(bienvenida);

    bool quitMessage = false;
    while (!quitMessage) {
        std::string message = this->protocol.receive();
    
        std::cout << "Message: " << message << std::endl;
        quitMessage = message == QUIT_STRING;
    }
}

void ClientAttendant::forceShutdown() {
    this->protocol.forceShutDown();
}

ClientAttendant::~ClientAttendant() = default;








