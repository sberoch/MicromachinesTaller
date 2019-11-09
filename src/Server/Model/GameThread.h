#ifndef MICROMACHINES_GAMETHREAD_H
#define MICROMACHINES_GAMETHREAD_H

#include <vector>
#include "Car/Car.h"
#include "World.h"
#include "../Network/ThClient.h"
#include <thread>

class GameThread {
private:
    World _world;
    std::vector<Track*> _track;
    std::vector<Grass*> _grass;
    HealthPowerup* _hPowerup;
    BoostPowerup* _bPowerup;
    Mud* _mud;
    Rock* _rock;
    Oil* _oil;
    std::shared_ptr<Configuration> _configuration;

    bool _gameToStart, _gameStarted, _gameEnded;
public:
    GameThread(size_t n_of_players, const std::shared_ptr<Configuration>& configuration);
    void run(std::atomic_bool& running, SafeQueue<std::shared_ptr<Event>>& incomingEvents,
            std::unordered_map<int ,std::shared_ptr<ClientThread>>& clients);
    void join();
    ~GameThread();
    json getSerializedMap();
    std::shared_ptr<Car> createCar(int id);
    void step();

    void startGame();
};

#endif //MICROMACHINES_GAMETHREAD_H
