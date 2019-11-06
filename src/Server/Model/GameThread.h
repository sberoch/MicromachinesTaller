#ifndef MICROMACHINES_GAMETHREAD_H
#define MICROMACHINES_GAMETHREAD_H

#include <vector>
#include "Car/Car.h"
#include "World.h"
#include <thread>

class GameThread {
private:
    World _world;
    std::shared_ptr<Configuration> _configuration;

    bool _gameToStart, _gameStarted, _gameEnded;
    std::thread _gameLoop;

public:
    GameThread(size_t n_of_players, std::shared_ptr<Configuration> configuration);
    void run();
    void join();
    ~GameThread();
};

#endif //MICROMACHINES_GAMETHREAD_H
