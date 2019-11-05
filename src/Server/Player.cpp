#include "Player.h"
#include "../Common/Event/SnapshotEvent.h"
#include <iostream>

Player::Player(Socket socket, Car* car, size_t id) : _protocol(std::move(socket)), _car(car), _id(id){}

void Player::handleInput(const InputEnum& input){
    _car->handleInput(input);
    _car->update();
}

void Player::receive(std::string& received){
    received = _protocol.receive();
}

void Player::send(){
    std::cout << "Sending\n";
    SnapshotEvent snap;
    Status status = _car->getStatus();

    int type = -1;
    switch (status) {
        case NOTHING :
            break;
        case GRABBED_HEALTH_POWERUP :
            type = TYPE_HEALTH_POWERUP;
            break;
    }

    if (type != -1){
        std::cout << "Removing hearth pu\n";
        snap.removeGameItem(type, 3);
    }

    snap.setCar(_car->x(), _car->y(), _car->angle() * RADTODEG, _car->health(), _id); //TODO: id hardcodeado
    snap.send(_protocol);
}

void Player::sendStart(json j) {
    SnapshotEvent snap;
    snap.setMap(std::move(j));
    snap.setPlayerId(_id);
    snap.setMudSplatEvent();
    snap.addGameItem(TYPE_HEALTH_POWERUP, 16, 10, 0, 3);
    snap.addGameItem(TYPE_BOOST_POWERUP, 14, 10, 0, 4);
    snap.addGameItem(TYPE_ROCK, 14, 8, 0, 5);
    snap.addGameItem(TYPE_OIL, 9, 14, 90, 6);
    snap.send(_protocol);
}