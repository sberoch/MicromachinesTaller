#include "Player.h"
#include "../Common/Event/SnapshotEvent.h"
#include <iostream>

Player::Player(std::shared_ptr<Car> car, size_t id) :_car(car), _id(id){}

void Player::handleInput(const InputEnum& input){
    _car->handleInput(input);
    _car->update();
}

void Player::receive(std::string& received, Protocol& protocol){
    received = protocol.receive();
}

SnapshotEvent* Player::makeSnapshot(){
    std::cout << "Sending\n";
    SnapshotEvent* snap = new SnapshotEvent();
    snap->setCar(_car->x(), _car->y(), _car->angle() * RADTODEG, _car->health(), 0); //TODO: id hardcodeado
    return snap;
}

void Player::sendStart(json j, Protocol& protocol) {
    SnapshotEvent snap;
    snap.setMap(std::move(j));
    snap.setPlayerId(_id);
    snap.setMudSplatEvent();
    snap.send(protocol);
}

void Player::assignCar(std::shared_ptr<Car> newCar) {
    this->_car = std::move(newCar);
}
