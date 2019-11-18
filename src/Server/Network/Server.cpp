//
// Created by alvaro on 30/10/19.
//

#include "Server.h"
#include "../../Common/Socket.h"
#include "AcceptingThread.h"

#define Q_MINUSCULA 'q'

#define qCHAR 'q'

Server::Server(const char* portNumber):
                    acceptSocket(Socket::createAcceptingSocket(portNumber)) {}

void Server::run(){
    std::cout << "Servidor creado" << std::endl;
    AcceptingThread acceptor(acceptSocket);
    acceptor.start();

    char c;
    while ((c = std::cin.get()) != qCHAR) {}

    acceptSocket.stop();

    acceptor.join();
}



Server::~Server() = default;
