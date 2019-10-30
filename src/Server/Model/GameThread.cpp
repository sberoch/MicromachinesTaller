#include "GameThread.h"
#include <iostream>

GameThread::GameThread(size_t n_of_players) : _world(n_of_players), _cars() {
    for (size_t i=0; i<n_of_players; ++i) {
        _cars.push_back(new Car(_world.createCar(i)));
    }
    _tire = _world.createTire();
}

std::vector<Car*> GameThread::getCars(){
    return _cars;
}

Tire* GameThread::getTire(){
    return _tire;
}

void GameThread::update(int control){
    //_tire->updateTraction();
    _tire->updateDrive(control);
    _tire->updateTurn(control);

    _world.step(8, 3);
}

void GameThread::update(Input movInput, Input turnInput){
    for (size_t i=0; i<_cars.size(); ++i){
        _cars[i]->handleInput(movInput, turnInput);
        _cars[i]->update();
    }
    //_tire->updateFriction();
    //_tire->updateDrive(movInput);
    //_tire->updateTurn(turnInput);

    _world.step(8, 3);
}

GameThread::~GameThread() {
	for (auto& car : _cars) {
		delete car;
	}
}
