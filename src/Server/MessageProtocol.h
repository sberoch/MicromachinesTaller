//
// Created by alvaro on 28/9/19.
//

#ifndef HONEYPOT_SERVERPROTOCOL_H
#define HONEYPOT_SERVERPROTOCOL_H


#include "../Common/Socket.h"
#include <vector>
#include <list>

class MessageProtocol {
private:
    Socket skt;

public:
    //Crea el protocolo de comunicacion, moviendo el socket de la
    // intercomunicacion cliente servidor al mismo.
    explicit MessageProtocol(Socket skt);

    //Recibe un mensaje hasta detectar un caracter '\n'.
    std::string messageReceive();

    //Destructor por default.
    ~MessageProtocol();

    //Divide el message segun el delimitador recibido por parametro. Cada
    //division es guardada en un vector de strings y devuelto.
    static std::vector<std::string> splitCommand(std::string &message,
            char delim);

    //Envia el mensaje, agregando un '\n' al final.
    void messageSend(std::string &message);

    void forceShutDown();
};


#endif //HONEYPOT_SERVERPROTOCOL_H
