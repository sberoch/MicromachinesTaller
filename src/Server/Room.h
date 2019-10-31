//
// Created by alvaro on 29/10/19.
//

#ifndef MICROMACHINES_ROOM_H
#define MICROMACHINES_ROOM_H


#include "ThClient.h"

class Room: public Thread{
private:
    std::vector<std::shared_ptr<ClientThread>> clients;
public:
    Room();

    void run() override;

    void addClient(const std::shared_ptr<ClientThread>& newClient);

    bool isDead() override {
        return false;
    }

    //No utilizado
    void stop() override {}

    ~Room() override;
};


#endif //MICROMACHINES_ROOM_H
