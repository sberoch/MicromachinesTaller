//
// Created by alvaro on 29/10/19.
//

#ifndef MICROMACHINES_ROOM_H
#define MICROMACHINES_ROOM_H


#include "ThClient.h"
<<<<<<< Updated upstream:src/Server/Room.h
=======
#include "../../Common/Thread.h"
#include "../Model/Game.h"
>>>>>>> Stashed changes:src/Server/Network/Room.h

class Room: public Thread{
private:
    std::vector<std::shared_ptr<ClientThread>> clients;
<<<<<<< Updated upstream:src/Server/Room.h
=======
    std::atomic<bool> running;
    Game game;
>>>>>>> Stashed changes:src/Server/Network/Room.h
public:
    explicit Room(int amountOfClients);

    void run() override;

    void addClient(const std::shared_ptr<ClientThread>& newClient);

<<<<<<< Updated upstream:src/Server/Room.h
    bool isDead() override {
        return false;
    }

    //No utilizado
    void stop() override {}
=======
    void stop();

    std::shared_ptr<Car> createCar(int id);
>>>>>>> Stashed changes:src/Server/Network/Room.h

    ~Room() override;
};


#endif //MICROMACHINES_ROOM_H
