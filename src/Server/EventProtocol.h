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
    EventProtocol(Socket socket);

    ~EventProtocol();

    std::string receive();

    void send(std::string message);
};


#endif //MICROMACHINES_EVENTPROTOCOL_H
