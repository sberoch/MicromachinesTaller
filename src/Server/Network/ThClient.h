//
// Created by alvaro on 30/9/19.
//

#ifndef HONEYPOT_SERVERTHCLIENT_H
#define HONEYPOT_SERVERTHCLIENT_H


#include <atomic>
#include "RoomController.h"
#include "../../Common/Protocol.h"
#include "../../Common/Event/Event.h"
#include "../Player.h"
#include "EventReceiver.h"
#include "EventSender.h"

#define QUIT_STRING "QUIT"

class ClientThread: public Thread {
private:
    std::atomic<bool> keepTalking;
    Protocol protocol;
    RoomController& controller;
    int id;
    Player player;
    SafeQueue<std::shared_ptr<Event>> receivingNonBlockingQueue;
    SafeQueue<std::shared_ptr<Event>> sendingBlockingQueue;
    EventReceiver receiver;
    EventSender sender;

public:
    //Inicializa la variable atomica booleana y el atendedor de clientes.
    //Para este ultimo mueve el socket de la comunicacion.
    ClientThread(Protocol protocol, RoomController& controller, int clientId,
            std::shared_ptr<Car> car);

    void run() override;

    //Detiene la ejecucion del cliente y pone la variable booleana en falso
    //para que el recolector de clientes muertos pueda reconocerlo como tal.
    void stop();

    //Si el cliente ya produjo el stop o termino de hablar, devuelve true.
    bool isDead();

    ~ClientThread() override= default;

    void sendEvent(const std::shared_ptr<Event>& event);
    void handleInput(const InputEnum& input);
    void sendFromPlayer();
    std::shared_ptr<Event> popFromNonBlockingQueue();
};




#endif //HONEYPOT_SERVERTHCLIENT_H
