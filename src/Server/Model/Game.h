#ifndef MICROMACHINES_GAME_H
#define MICROMACHINES_GAME_H

#include <vector>
#include "Car/Car.h"
#include "World.h"
#include "Car/Tire.h"

class Game {
private:
    World _world;
    std::vector<Car*> _cars;
    Tire* _tire;

public:
    Game(size_t n_of_players);
    void update(Input movInput, Input turnInput);

    void update(int control);
    std::vector<Car*> getCars();
    Tire* getTire();
    ~Game();
};

#endif //MICROMACHINES_GAME_H
