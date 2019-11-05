#include "Player.h"
#include "../Common/ServerSnapshot.h"

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
    snap.setCar(_car->x(), _car->y(), _car->angle() * RADTODEG, _car->health(), 1); //TODO: id hardcodeado
    snap.send(_protocol);
}

void Player::sendStart(json j) {
    SnapshotEvent snap;
    snap.setMap(std::move(j));
    snap.setPlayerId(_id);
    snap.setMudSplatEvent();
    snap.send(_protocol);
}