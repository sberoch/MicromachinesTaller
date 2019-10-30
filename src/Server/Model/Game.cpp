#include "Game.h"
#include <iostream>

Game::Game(size_t n_of_players) : _world(n_of_players), _cars() {
    for (size_t i=0; i<n_of_players; ++i) {
        _cars.push_back(new Car(_world.createCar(i)));
    }
    _tire = _world.createTire();
}

std::vector<Car*> Game::getCars(){
    return _cars;
}

Tire* Game::getTire(){
    return _tire;
}

void Game::update(int control){
    //_tire->updateTraction();
    _tire->updateDrive(control);
    _tire->updateTurn(control);

    _world.step(8, 3);
}

void Game::update(Input movInput, Input turnInput){
    for (size_t i=0; i<_cars.size(); ++i){
        _cars[i]->handleInput(movInput, turnInput);
        _cars[i]->update();
    }
    //_tire->updateFriction();
    //_tire->updateDrive(movInput);
    //_tire->updateTurn(turnInput);

    _world.step(8, 3);
}

Game::~Game() {
	for (auto& car : _cars) {
		delete car;
	}
}
