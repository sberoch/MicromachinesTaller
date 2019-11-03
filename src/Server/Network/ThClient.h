//
// Created by alvaro on 30/9/19.
//

#ifndef HONEYPOT_SERVERTHCLIENT_H
#define HONEYPOT_SERVERTHCLIENT_H


#include <atomic>
#include "RoomController.h"
#include "../../Common/Protocol.h"

#define QUIT_STRING "QUIT"

class ClientThread: public Thread {
private:
    std::atomic<bool> keepTalking;
    Protocol protocol;
    SafeQueue<std::string> nonBlockingQueue;
    RoomController& controller;
    int id;

public:
    //Inicializa la variable atomica booleana y el atendedor de clientes.
    //Para este ultimo mueve el socket de la comunicacion.
    explicit ClientThread(Protocol protocol, RoomController& controller, int clientId);

    int askForRoomId();

    void run() override;

    std::string popElement();

    //Detiene la ejecucion del cliente y pone la variable booleana en falso
    //para que el recolector de clientes muertos pueda reconocerlo como tal.
    void stop() override;

    //Si el cliente ya produjo el stop o termino de hablar, devuelve true.
    bool isDead() override;

    ~ClientThread() override= default;

    void sendEvent();
};




#endif //HONEYPOT_SERVERTHCLIENT_H
