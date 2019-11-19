#include "Player.h"
#include "../Common/Event/SnapshotEvent.h"
#include <iostream>
#include <utility>
#include "../Server/Model/Car/Car.h"

Player::Player(std::shared_ptr<Car> car, int& inRoomId) :
                        _car(std::move(car)),
                        inRoomId(inRoomId),
                        _modifierToAdd(false),
                        _modifierDTO(new ModifierDTO()) {}

void Player::update(){
    _car->update();
}


void Player::handleInput(const InputEnum& input){
    _car->handleInput(input);
    //_car->update();

    std::vector<Effect*> aux;
    for (int i=0; i<_effects.size(); ++i){
        _effects[i]->timeOfAction --;
        if (_effects[i]->timeOfAction == 0){
            _car->stopEffect(_effects[i]->type);
            delete _effects[i];
        } else {
            aux.push_back(_effects[i]);
        }
    }
    _effects.swap(aux);
}

void Player::receive(std::string& received, Protocol& protocol){
    received = protocol.receive();
}

void Player::_addEffect(const int& effectType, const int& timeOfAction){
    Effect* effect = new Effect;
    effect->type = effectType;
    effect->timeOfAction = timeOfAction;
    _effects.push_back(effect);
}

void Player::createModifier(const size_t& type, const size_t& id, const float& x, const float& y, const float& angle){
    _modifierToAdd = true;
    _modifierDTO->id = id;
    _modifierDTO->type = type;
    _modifierDTO->x = x;
    _modifierDTO->y = y;
    _modifierDTO->angle = angle;
}


void Player::modifySnapshot(const std::shared_ptr<SnapshotEvent>& snapshot){
    std::vector<Status *> status = _car->getStatus();

    for (size_t i=0; i<status.size(); ++i){
        switch (status[i]->status) {
            case NOTHING :
                break;
            case EXPLODED:
                snapshot->addGameItem(TYPE_EXPLOSION, _car->x(), _car->y(), _car->angle(), 0);
                break;
            case GRABBED_HEALTH_POWERUP :
                snapshot->removeGameItem(TYPE_HEALTH_POWERUP, status[i]->id);
                break;
            case GRABBED_BOOST_POWERUP :
                _addEffect(TYPE_BOOST_POWERUP, status[i]->timeOfAction);
                snapshot->removeGameItem(TYPE_BOOST_POWERUP, status[i]->id);
                break;
            case GRABBED_MUD :
                snapshot->setMudSplatEvent();
                snapshot->removeGameItem(TYPE_MUD, status[i]->id);
                break;
            case GRABBED_ROCK :
                snapshot->removeGameItem(TYPE_ROCK, status[i]->id);
                break;
            case GRABBED_OIL :
                _addEffect(TYPE_OIL, status[i]->timeOfAction);
                snapshot->removeGameItem(TYPE_OIL, status[i]->id);
                break;
            case WINNED :
                snapshot->setGameOver(inRoomId);
                break;
        }
    }

    _car->resetStatus();

    if (_modifierToAdd){
        snapshot->addGameItem(_modifierDTO->type, _modifierDTO->x, _modifierDTO->y, _modifierDTO->angle, _modifierDTO->id);
        _modifierToAdd = false;
    }

    snapshot->setCar(_car->x(), _car->y(), _car->angle() * RADTODEG, _car->health(), inRoomId);
}

std::shared_ptr<SnapshotEvent> Player::sendStart(json j) {
    std::shared_ptr<SnapshotEvent> snap(new SnapshotEvent);
    snap->setMap(j);
    snap->signalMapReady();
    return snap;
}

void Player::assignCarAndId(std::shared_ptr<Car> newCar) {
    newCar->assignId(this->inRoomId);
    this->_car = std::move(newCar);
}
