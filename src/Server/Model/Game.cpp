#include "Game.h"
#include <iostream>

Game::Game(size_t n_of_players) : _world(n_of_players), _cars() {
    for (size_t i=0; i<n_of_players; ++i) {
        _cars.push_back(new Car(_world.createCar(i)));
    }
}

std::vector<Car*> Game::getCars(){
    return _cars;
}

void Game::update(Input movInput, Input turnInput){
    for (size_t i=0; i<_cars.size(); ++i){
        _cars[i]->handleInput(movInput, turnInput);
        _cars[i]->update();
    }
    _world.step(8, 3);
}

Game::~Game() {
	for (auto& car : _cars) {
		delete car;
	}
}
