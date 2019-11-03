//
// Created by alvaro on 29/10/19.
//

#ifndef MICROMACHINES_ROOM_H
#define MICROMACHINES_ROOM_H


#include <vector>
#include <memory>
#include "ThClient.h"
#include "Thread.h"

class Room: public Thread{
private:
    std::vector<std::shared_ptr<ClientThread>> clients;
    std::atomic<bool> running;
public:
    Room();

    void run() override;

    void addClient(const std::shared_ptr<ClientThread>& newClient);

    bool isDead() override;

    //No utilizado
    void stop() override;

    ~Room() override;
};


#endif //MICROMACHINES_ROOM_H
