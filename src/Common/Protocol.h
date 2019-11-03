//
// Created by alvaro on 23/10/19.
//

#ifndef MICROMACHINES_EVENTPROTOCOL_H
#define MICROMACHINES_EVENTPROTOCOL_H


#include <vector>
#include "Socket.h"

class Protocol {
private:
    Socket socket;
public:
	Protocol(const std::string &portName, const std::string &hostNumber);
	
    explicit Protocol(Socket socket);

    Protocol(Protocol &&other);

    ~Protocol();

    std::string receive();

    void send(std::string message);

    void forceShutDown();

    std::vector<std::string> splitCommand(std::string &message,
                                          char delim);
};


#endif //MICROMACHINES_EVENTPROTOCOL_H