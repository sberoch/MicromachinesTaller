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
#include "ClientAttendant.h"
#include "../Common/SocketError.h"
#include "../Common/SafeQueue.h"
#include <sstream>

#define QUIT_STRING "QUIT"

class ClientThread: public Thread {
private:
    std::atomic<bool> keepTalking;
    Protocol protocol;
    SafeQueue<std::string> nonBlockingQueue;
    int roomId;

public:
    //Inicializa la variable atomica booleana y el atendedor de clientes.
    //Para este ultimo mueve el socket de la comunicacion.
    explicit ClientThread(Protocol protocol):
                        keepTalking(true),
                        protocol(std::move(protocol)),
                        nonBlockingQueue(false),
                        roomId(0){}

    static int toInt(const std::string& string){
        std::stringstream ss(string);
        int x = 0;
        ss >> x;
        return x;
    }

    int getRoomId(){
        std::string message = "Ingrese el numero de sala: ";
        protocol.send(message);
        int id = toInt(protocol.receive());
        return id;
    }

    void run() override{
        try {
            while (this->keepTalking) {
                try {
                    protocol.send("Bienvenide");

                    bool quitMessage = false;
                    while (!quitMessage) {
                        std::string message = this->protocol.receive();
                        quitMessage = message == QUIT_STRING;
                        if (!quitMessage){
                            std::cout << "Pushing: " << message << std::endl;
                            this->nonBlockingQueue.push(message);
                        } else {
                            std::cout << "Quitting" << std::endl;
                        }
                    }
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

    std::string popElement(){
        std::string element;
        this->nonBlockingQueue.pop(element);
        return element;
    }

    //Detiene la ejecucion del cliente y pone la variable booleana en falso
    //para que el recolector de clientes muertos pueda reconocerlo como tal.
    void stop() override{
        protocol.forceShutDown();
        keepTalking = false;
    }

    //Si el cliente ya produjo el stop o termino de hablar, devuelve true.
    bool isDead() override{
        return !keepTalking;
    }

    ~ClientThread() override= default;
};


#endif //HONEYPOT_SERVERTHCLIENT_H
