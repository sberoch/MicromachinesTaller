//
// Created by alvaro on 10/10/19.
//

#ifndef HONEYPOT_COMMONCLOSEDSOCKET_H
#define HONEYPOT_COMMONCLOSEDSOCKET_H

#include <exception>

class SocketError : public std::exception {
public:
    const char* what() const noexcept override{
        return "Socket cerrado";
    }
};

#endif //HONEYPOT_COMMONCLOSEDSOCKET_H
