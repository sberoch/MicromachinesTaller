#include "Game.h"
#include "../../Common/Socket.h"
#include "../../Common/Protocol.h"
#include "../../Common/InputEnum.h"
#include "../Player.h"
#include "../../Common/SocketError.h"
#include <iostream>

#include "../../Common/Event/EventCreator.h"

using namespace std::chrono;

Game::Game(size_t n_of_players, std::shared_ptr<Configuration> configuration) :
                                             _configuration(configuration),
                                             _world(n_of_players, configuration),
                                             _cars(), _track(), _grass(), _gameToStart(true),
                                             _gameStarted(true),
                                             _gameEnded(false){
                                             //_gameLoop(&Game::run, this){
    _world.createTrack(_track);
    _world.createGrass(_grass);
}

void Game::step(){
    _world.step(_configuration->getVelocityIterations(), _configuration->getPositionIterations());
}

Car* Game::createCar(int id){
    return this->_world.createCar(id);
}

void Game::run(){
    try {
        //EventCreator eventCreator;

        //Get initial time
        //std::clock_t begin = clock();

        //player.send();
        //player.receive(cmd);
            
//        std::shared_ptr<Event> event = eventCreator.makeEvent(cmd);
        //player.handleInput((InputEnum) event->j["cmd_id"].get<int>());

        //Step del world
        _world.step(_configuration->getVelocityIterations(), _configuration->getPositionIterations());

        //player.send();
        //Sleep
//        std::clock_t end = clock();
//        double execTime = double(end - begin) / (CLOCKS_PER_SEC / 1000);
//        double frames = 25;
//        if (execTime < frames) {
//            int to_sleep = (frames - execTime);
//            std::this_thread::sleep_for(std::chrono::milliseconds(to_sleep));
//        }
    } catch(SocketError& se){
        std::cerr << se.what();
    } catch(...) {
        std::cerr << "Game Thread: UnknownException.\n";
    }
}

void Game::join(){
    _gameLoop.join();
}

std::vector<Car*> Game::getCars(){
    return _cars;
}

void Game::update(Input movInput, Input turnInput){
    for (size_t i=0; i<_cars.size(); ++i){
        _cars[i]->handleInput(movInput, turnInput);
        _cars[i]->update();
    }

    _world.step(_configuration->getVelocityIterations(), _configuration->getPositionIterations());
}

Game::~Game() {

}
