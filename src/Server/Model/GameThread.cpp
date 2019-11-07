#include "GameThread.h"
#include "../../Common/Socket.h"
#include "../../Common/Protocol.h"
#include "../Player.h"
#include "../../Common/SocketError.h"
#include <iostream>
#include "../../Common/Event/EventCreator.h"
#include "../Network/ThClient.h"

using namespace std::chrono;

GameThread::GameThread(size_t n_of_players, const std::shared_ptr<Configuration>& configuration) :
                                             _configuration(configuration),
                                             _world(n_of_players, configuration),
                                             _track(), _grass(), _gameToStart(true),
                                             _gameStarted(true),
                                             _gameEnded(false){
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
    std::shared_ptr<Event> event;
    while (running) {
        try {
            std::clock_t begin = clock();

            if (!clients.empty()) {
                while (incomingEvents.get(event)) {
//                    clients[event->j["client_id"]]->handleInput((InputEnum) event->j["cmd_id"].get<int>());
                    clients[0]->handleInput((InputEnum) event->j["cmd_id"].get<int>());
                }
            }

            step();

            for (auto &actualClient : clients) {
                actualClient.second->sendSnapshot();
            }


            std::clock_t end = clock();
            double execTime = double(end - begin) / (CLOCKS_PER_SEC / 1000);
            double frames = 35;
            if (execTime < frames) {
                int to_sleep = (frames - execTime);
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(to_sleep));
            }
        } catch (SocketError &se) {
            running = false;
            std::cerr << se.what();
        } catch (...) {
            running = false;
            std::cerr << "Game Thread: UnknownException.\n";
        }
    }
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
