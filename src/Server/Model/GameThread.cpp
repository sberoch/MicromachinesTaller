#include "GameThread.h"
#include <iostream>

using namespace std::chrono;

GameThread::GameThread(size_t n_of_players, std::shared_ptr<Configuration> configuration) :
                                             _world(n_of_players, configuration),
                                             _cars(), _gameToStart(true),
                                             _gameStarted(false),
                                             _gameEnded(false) {
    for (size_t i=0; i<n_of_players; ++i)
        _cars.push_back(_world.createCar(i));

}

void GameThread::run(){
    try {
        while(_gameStarted) {
            //Get initial time
            std::clock_t begin = clock();



            //Sleep
            std::clock_t end = clock();
            double execTime = double(end - begin) / (CLOCKS_PER_SEC/1000);
            if (execTime < 25){
                int to_sleep =  (25 - execTime);
                std::this_thread::sleep_for(std::chrono::milliseconds(to_sleep));
            }
        }
    } catch(...) {
        std::cerr << "Game Thread: UnknownException.\n";
    }
}

std::vector<Car*> GameThread::getCars(){
    return _cars;
}

void GameThread::update(Input movInput, Input turnInput){
    for (size_t i=0; i<_cars.size(); ++i){
        _cars[i]->handleInput(movInput, turnInput);
        _cars[i]->update();
    }

    _world.step(8, 3);
}

GameThread::~GameThread() {
	for (auto& car : _cars) {
		delete car;
	}
}
