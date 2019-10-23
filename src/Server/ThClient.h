//
// Created by alvaro on 30/9/19.
//

#ifndef HONEYPOT_SERVERTHCLIENT_H
#define HONEYPOT_SERVERTHCLIENT_H


#include <iostream>
#include <mutex>
#include <atomic>
#include <cstring>
#include "Thread.h"
#include "../Common/Socket.h"
#include "MessageProtocol.h"
#include "ClientAttendant.h"
#include "../Common/SocketError.h"

class ClientThread: public Thread {
private:
    std::atomic<bool> keepTalking;
    ClientAttendant attendant;

public:
    //Inicializa la variable atomica booleana y el atendedor de clientes.
    //Para este ultimo mueve el socket de la comunicacion.
    explicit ClientThread(Socket skt):
                        keepTalking(true),
                        attendant(std::move(skt)) {}

    void run() override{
        try {
            while (this->keepTalking) {
                try {
                    this->attendant.receivingLoop();
                } catch (SocketError &e) {
                    keepTalking = false;
                }
                keepTalking = false;
            }
        }  catch(const std::exception &e) {
                printf("ERROR from thClient: %s \n", e.what());
        } catch(...) {
                printf("Unknown error from thclient");
        }
    }

    //Detiene la ejecucion del cliente y pone la variable booleana en falso
    //para que el recolector de clientes muertos pueda reconocerlo como tal.
    void stop() override{
        attendant.forceShutdown();
        keepTalking = false;
    }

    //Si el cliente ya produjo el stop o termino de hablar, devuelve true.
    bool isDead() override{
        return !keepTalking;
    }

    ~ClientThread() override= default;
};


#endif //HONEYPOT_SERVERTHCLIENT_H
