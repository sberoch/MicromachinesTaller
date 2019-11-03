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
    ServerSnapshot snap;
    snap.setCar(_car->x(), _car->y(), _car->angle() * RADTODEG, _car->health(), _id);
    snap.send(_protocol);
}