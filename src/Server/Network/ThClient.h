//
// Created by alvaro on 30/9/19.
//

#ifndef HONEYPOT_SERVERTHCLIENT_H
#define HONEYPOT_SERVERTHCLIENT_H


#include <atomic>
#include <iostream>
#include "RoomController.h"
#include "../../Common/Protocol.h"
#include "../../Common/Event/Event.h"
#include "../Player.h"
#include "EventReceiver.h"
#include "EventSender.h"
#include "../../Common/Event/EndSnapshot.h"

#define QUIT_STRING "QUIT"

class ClientThread {
private:
    std::atomic<bool> keepTalking;
    Protocol protocol;
    int clientId;
    int idFromRoom;
    Player player;
    SafeQueue<std::shared_ptr<Event>>* receivingNonBlockingQueue;
    SafeQueue<std::shared_ptr<Event>> sendingBlockingQueue;
    EventReceiver receiver;
    EventSender sender;

public:
    //Inicializa la variable atomica booleana y el atendedor de clientes.
    //Para este ultimo mueve el socket de la comunicacion.
    ClientThread(Protocol protocol, RoomController& controller, int clientId,
                    std::atomic_bool& acceptSocketRunning);
    void start();
    void run();

    //Detiene la ejecucion del cliente y pone la variable booleana en falso
    //para que el recolector de clientes muertos pueda reconocerlo como tal.
    void stop();

    //Si el cliente ya produjo el stop o termino de hablar, devuelve true.
    bool isDead();

    ~ClientThread() {
        std::cout << "Destruyendo client thread con clientId: " << clientId << std::endl;
    };

    void sendEvent(const std::shared_ptr<Event>& event);
    void handleInput(const InputEnum& input);
    void sendSnapshot(const std::shared_ptr<SnapshotEvent>& snapshot);
    void sendStart(json j);

    void assignRoomQueue(SafeQueue<std::shared_ptr<Event>>* receiveingQueue);

    void assignCar(const std::shared_ptr<Car>& car);

    void sendLobbySnapshot(std::shared_ptr<LobbySnapshot>& snapshot);

    void
    modifySnapshotFromClient(const std::shared_ptr<SnapshotEvent> &snapshot);

    void createModifier(const size_t& type, const size_t& id, const float& x,
            const float& y, const float& angle);

    void update();

    void assignIdFromRoom(int idFromRoom);

    int getIdFromRoom();

    bool finishedPlaying();

    void sendEndEvent(const std::shared_ptr<EndSnapshot> &endSnapshot);
};




#endif //HONEYPOT_SERVERTHCLIENT_H
