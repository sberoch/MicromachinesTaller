#include "Game.h"

Game::Game(size_t n_of_players) : _world(n_of_players), _cars() {
    for (size_t i=0; i<n_of_players; ++i){
        _cars[i] = Car(_world.createCar(i));
    }
}

void Game::update(){
    _world.step(8, 3);
}

Game::~Game(){}
