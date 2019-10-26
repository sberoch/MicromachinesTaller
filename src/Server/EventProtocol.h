//
// Created by alvaro on 23/10/19.
//

#ifndef MICROMACHINES_EVENTPROTOCOL_H
#define MICROMACHINES_EVENTPROTOCOL_H


#include "../Common/Socket.h"

class EventProtocol {
private:
    Socket socket;
public:
    explicit EventProtocol(Socket socket);

    ~EventProtocol();

    std::string receive();

    void send(std::string message);

    void forceShutDown();
};


#endif //MICROMACHINES_EVENTPROTOCOL_H