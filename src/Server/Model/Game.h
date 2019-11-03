#ifndef MICROMACHINES_GAME_H
#define MICROMACHINES_GAME_H

#include <vector>
#include "Car/Car.h"
#include "World.h"
#include <thread>

class Game {
private:
    World _world;
    std::vector<Car*> _cars;
    std::vector<Track*> _track;
    std::vector<Grass*> _grass;
    std::shared_ptr<Configuration> _configuration;

    bool _gameToStart, _gameStarted, _gameEnded;
    std::thread _gameLoop;

public:
    Game(size_t n_of_players, std::shared_ptr<Configuration> configuration);
    void update(Input movInput, Input turnInput);

    void run();
    void join();

    std::vector<Car*> getCars();
    ~Game();

    void step();

    Car *createCar(int id);
};

#endif //MICROMACHINES_GAME_H
