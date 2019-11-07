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

void Player::createModifier(const size_t& type, const size_t& id, const float& x, const float& y, const float& angle){
    SnapshotEvent snap;
    snap.addGameItem(type, x, y, angle, id);
    snap.send(_protocol);
}

void Player::send(){
    SnapshotEvent snap;
    Status status = _car->getStatus();

    switch (status) {
        case NOTHING :
            break;
        case GRABBED_HEALTH_POWERUP :
            snap.removeGameItem(TYPE_HEALTH_POWERUP, 3);
            break;
        case GRABBED_BOOST_POWERUP :
            snap.removeGameItem(TYPE_BOOST_POWERUP, 4);
            break;
        case GRABBED_MUD :
            snap.setMudSplatEvent();
            break;
        case GRABBED_ROCK :
            snap.removeGameItem(TYPE_ROCK, 5);
            break;
        case GRABBED_OIL :
            snap.removeGameItem(TYPE_OIL, 6);
            break;
    }

    snap.setCar(_car->x(), _car->y(), _car->angle() * RADTODEG, _car->health(), _id); //TODO: id hardcodeado
    snap.send(_protocol);
}

void Player::sendStart(json j) {
    SnapshotEvent snap;
    snap.setMap(std::move(j));
    snap.setPlayerId(_id);
    snap.addGameItem(TYPE_HEALTH_POWERUP, 16, 10, 0, 3);
    snap.addGameItem(TYPE_BOOST_POWERUP, 14, 10, 0, 4);
    snap.addGameItem(TYPE_ROCK, 14, 8, 0, 5);
    snap.addGameItem(TYPE_OIL, 9, 14, 90, 6);
    snap.addGameItem(TYPE_MUD, 21, 6, 0, 5);
    snap.send(_protocol);
}