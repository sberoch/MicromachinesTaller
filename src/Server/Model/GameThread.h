#ifndef MICROMACHINES_GAMETHREAD_H
#define MICROMACHINES_GAMETHREAD_H

#include <vector>
#include "Car/Car.h"
#include "World.h"
#include <thread>

class GameThread {
private:
    World _world;
    std::vector<Car*> _cars;
    std::vector<Track*> _track;
    std::vector<Grass*> _grass;
    HealthPowerup* _hPowerup;
    BoostPowerup* _bPowerup;

    std::shared_ptr<Configuration> _configuration;

    bool _gameToStart, _gameStarted, _gameEnded;
    std::thread _gameLoop;

public:
    GameThread(size_t n_of_players, std::shared_ptr<Configuration> configuration);
    void update(Input movInput, Input turnInput);

    void run();
    void join();

    std::vector<Car*> getCars();
    ~GameThread();
};

#endif //MICROMACHINES_GAMETHREAD_H
