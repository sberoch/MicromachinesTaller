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
<<<<<<< Updated upstream
    explicit EventProtocol(Socket socket);
=======
    EventProtocol(Socket socket);
>>>>>>> Stashed changes

    ~EventProtocol();

    std::string receive();

    void send(std::string message);
<<<<<<< Updated upstream

    void forceShutDown();
=======
>>>>>>> Stashed changes
};


#endif //MICROMACHINES_EVENTPROTOCOL_H
