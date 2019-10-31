//
// Created by alvaro on 30/10/19.
//

#include "Server.h"
#include "../Common/Socket.h"
#include "AcceptingThread.h"

#define Q_MINUSCULA 'q'

Server::Server(const char* portNumber): portNumber(portNumber) {
    run();
}

void Server::run(){
    Socket acceptSocket = Socket::createAcceptingSocket(portNumber);

    AcceptingThread acceptor(acceptSocket);
    acceptor.start();

    char c = (char) getchar();

    if (c == Q_MINUSCULA){
        acceptSocket.stop();
    }
    acceptor.join();
}



Server::~Server() {

}
