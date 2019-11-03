//
// Created by alvaro on 30/10/19.
//

#ifndef MICROMACHINES_SERVER_H
#define MICROMACHINES_SERVER_H


#include "Room.h"
#include <list>

class Server {
private:
    Socket acceptSocket;
public:
    explicit Server(const char* portNumber);

    ~Server();

    void run();
};


#endif //MICROMACHINES_SERVER_H
