//
// Created by alvaro on 28/9/19.
//

#ifndef HONEYPOT_SERVERCLIENTATTENDANT_H
#define HONEYPOT_SERVERCLIENTATTENDANT_H

#include <unordered_map>
#include <set>
#include "../Common/Socket.h"
#include "../Common/Protocol.h"

class ClientAttendant {
private:
    EventProtocol protocol;

public:
    //Crea el atendedor, recibe el mapa, el socket con el que crea el protocolo
    // y el set protegido de directorios.
    explicit ClientAttendant(Socket skt);

    //Loop general, primero llama al logInLoop para chequear usuario y password
    //y luego ejecuta los comandos utilizando el factory method.
    void receivingLoop();

    //Default destructor.
    ~ClientAttendant();


    //Fuerza la detencion de la conexion.
    void forceShutdown();
};


#endif //HONEYPOT_SERVERCLIENTATTENDANT_H
