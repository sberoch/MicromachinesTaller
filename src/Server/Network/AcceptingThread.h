//
// Created by alvaro on 30/9/19.
//

#ifndef HONEYPOT_SERVERACCEPTINGTHREAD_H
#define HONEYPOT_SERVERACCEPTINGTHREAD_H


#include <iostream>
#include "Thread.h"
#include "../../Common/Socket.h"
#include "ThClient.h"
#include "Room.h"
#include "RoomController.h"
#include <list>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>

class AcceptingThread: public Thread {
private:
    Socket &acceptSocket;
    RoomController roomController;
    std::atomic_bool running;
    SafeCounter clientCounter;

public:
    //Asigna las referencias al socket aceptador y al archivo.
    explicit AcceptingThread(Socket &acceptSocket);

    //Realiza el ciclo aceptador con el recolector de clientes muertos hasta
    //que se cierra el socket aceptador. Luego de esto, se mata a todos los
    //clientes restantes liberando los recursos.
    void run() override;

    //No utilizado
    bool isDead() override {
        return false;
    }

    //No utilizado
    void stop() override {}

    //Detiene a todos los clientes que siguen en ejecucion.
    ~AcceptingThread() override;
};


#endif //HONEYPOT_SERVERACCEPTINGTHREAD_H
