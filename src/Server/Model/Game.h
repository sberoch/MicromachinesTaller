#ifndef MICROMACHINES_GAME_H
#define MICROMACHINES_GAME_H

#include <vector>
#include "Car.h"
#include "World.h"

class Game {
private:
    World _world;
    std::vector<Car> _cars;

public:
    Game(size_t n_of_players);
    ~Game();
};

#endif //MICROMACHINES_GAME_H
