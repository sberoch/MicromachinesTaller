//
// Created by alvaro on 29/10/19.
//

#include "Room.h"
#include "../Common/ServerSnapshot.h"

Room::Room(){}

void Room::run() {
//    std::string buffer;
//    float x, y;
//    int angle, health, id;
//    x = 15.0;
//    y = 7.0;
//    angle = 180;
//    health = 100, id = 11;

    //Recibo el comando y devuelvo el cambio de posicion/angulo. (muy basico)
    std::string concatenation;
    for (auto& client: clients){
        concatenation.append(client->popElement());
    }

    std::cout << "Concatenacion: " << concatenation << std::endl;

//    while (true) {
//            ServerSnapshot snap;
//            std::string cmd = protocol.receive();
//            if (cmd == "a") {
//                angle -= 10;
//                if (health >= 10) health -= 10;
//            } else if (cmd == "d") {
//                angle += 10;
//                if (health < 100) health += 10;
//            } else if (cmd == "w") {
//                y -= 0.2;
//            }
//            snap.setCar(x, y, angle, health, id);
//            snap.send(protocol);
//        }
}

void Room::addClient(const std::shared_ptr<ClientThread>& newClient) {
    this->clients.push_back(newClient);
}

Room::~Room() {
    for (auto& client: clients){
        client->stop();
        client->join();
    }
}
