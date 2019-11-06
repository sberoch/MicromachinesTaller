#include "GameThread.h"
#include "../../Common/Socket.h"
#include "../../Common/Protocol.h"
#include "../Player.h"
#include "../../Common/SocketError.h"
#include <iostream>
#include "../../Common/Event/EventCreator.h"
#include "../Network/ThClient.h"

using namespace std::chrono;

GameThread::GameThread(size_t n_of_players, std::shared_ptr<Configuration> configuration) :
                                             _configuration(configuration),
                                             _world(n_of_players, configuration),
                                             _track(), _grass(), _gameToStart(true),
                                             _gameStarted(true),
                                             _gameEnded(false){
                                             //_gameLoop(&GameThread::run, this){
    _world.createTrack(_track);
    _world.createGrass(_grass);
    _hPowerup = _world.createHealthPowerup();
    _bPowerup = _world.createBoostPowerup();
    _mud = _world.createMud();
    _rock = _world.createRock();
    _oil = _world.createOil();
}

void GameThread::run(std::atomic_bool& running, 
        SafeQueue<std::shared_ptr<Event>>& incomingEvents,
        std::unordered_map<int ,std::shared_ptr<ClientThread>>& clients){
    while (running) {
        try {
            std::clock_t begin = clock();

            std::shared_ptr<Event> event;

            if (!clients.empty()) {
                while (incomingEvents.get(event)) {
                    //clients[event->j["client_id"]]->handleInput((InputEnum) event->j["cmd_id"].get<int>());
                    clients.at(0)->handleInput(
                            (InputEnum) event->j["cmd_id"].get<int>());
                }
            }

            step();
            for (auto &actualClient : clients) {
                //actualClient->sen(event);
                actualClient.second->sendFromPlayer();
            }

            std::clock_t end = clock();
            double execTime = double(end - begin) / (CLOCKS_PER_SEC / 1000);
            double frames = 25;
            if (execTime < frames) {
                int to_sleep = (frames - execTime);
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(to_sleep));
            }
        } catch (SocketError &se) {
            std::cerr << se.what();
        } catch (...) {
            std::cerr << "Game Thread: UnknownException.\n";
        }
    }
}

void GameThread::join(){
    _gameLoop.join();
}

void GameThread::step(){
    _world.step(_configuration->getVelocityIterations(), _configuration->getPositionIterations());
}

GameThread::~GameThread() {}

json GameThread::getSerializedMap() {
    return _world.getSerializedMap();
}

std::shared_ptr<Car> GameThread::createCar(int id){
    return std::shared_ptr<Car>(_world.createCar(id));
}
