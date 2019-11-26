//
// Created by alvaro on 30/9/19.
//

#ifndef HONEYPOT_SERVERACCEPTINGTHREAD_H
#define HONEYPOT_SERVERACCEPTINGTHREAD_H


#include <iostream>
#include "../../Common/Thread.h"
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
    std::atomic_bool running;
    RoomController roomController;

public:
    //Asigna las referencias al socket aceptador y al archivo.
    explicit AcceptingThread(Socket &acceptSocket);

    //Realiza el ciclo aceptador con el recolector de clientes muertos hasta
    //que se cierra el socket aceptador. Luego de esto, se mata a todos los rooms
    //y clientes sin room. Los rooms matan a sus propios clientes.
    void run() override;

    ~AcceptingThread() override;
};


#endif //HONEYPOT_SERVERACCEPTINGTHREAD_H
