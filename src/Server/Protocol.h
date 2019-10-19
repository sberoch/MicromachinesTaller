//
// Created by alvaro on 28/9/19.
//

#ifndef HONEYPOT_SERVERPROTOCOL_H
#define HONEYPOT_SERVERPROTOCOL_H


#include "../Common/Socket.h"
#include <vector>
#include <list>

class Protocol {
private:
    Socket skt;

public:
    //Crea el protocolo de comunicacion, moviendo el socket de la
    // intercomunicacion cliente servidor al mismo.
    explicit Protocol(Socket skt);

    //Recibe un mensaje hasta detectar un caracter '\n'.
    std::string receive();

    //Destructor por default.
    ~Protocol();

    //Divide el message segun el delimitador recibido por parametro. Cada
    //division es guardada en un vector de strings y devuelto.
    static std::vector<std::string> splitCommand(std::string &message,
            char delim);

    //Envia el mensaje, agregando un '\n' al final.
    void send(std::string &message);

    static bool isACommand(std::string &command);

    void forceShutDown();
};


#endif //HONEYPOT_SERVERPROTOCOL_H
