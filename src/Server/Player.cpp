#include "Player.h"
#include "../Common/Event/SnapshotEvent.h"
#include <iostream>
#include <utility>

Player::Player(std::shared_ptr<Car> car, size_t id) :_car(std::move(car)), _id(id){}


void Player::handleInput(const InputEnum& input){
    _car->handleInput(input);
    _car->update();
}

void Player::receive(std::string& received, Protocol& protocol){
    received = protocol.receive();
}

void Player::modifySnapshot(const std::shared_ptr<SnapshotEvent>& snapshot){
    snapshot->setCar(_car->x(), _car->y(), _car->angle() * RADTODEG, _car->health(), _id);
}

std::shared_ptr<SnapshotEvent> Player::sendStart(json j) {
    std::shared_ptr<SnapshotEvent> snap(new SnapshotEvent);
    snap->setMap(j);
    snap->signalMapReady();
    return snap;
}

void Player::assignCar(std::shared_ptr<Car> newCar) {
    this->_car = std::move(newCar);
}
