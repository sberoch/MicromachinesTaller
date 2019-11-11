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
                                             _gameStarted(false),
                                             _gameEnded(false),
                                             roomRunning(true){
    _world.createTrack(_track);
    _world.createGrass(_grass);
    _hPowerup = _world.createHealthPowerup();
    _bPowerup = _world.createBoostPowerup();
    _mud = _world.createMud();
    _rock = _world.createRock();
    _oil = _world.createOil();
}

void GameThread::run(std::atomic_bool& serverRunning,
        SafeQueue<std::shared_ptr<Event>>& incomingEvents,
        std::unordered_map<int ,std::shared_ptr<ClientThread>>& clients){
    std::shared_ptr<Event> event;

    int i = 0;
    while (roomRunning && serverRunning) {
        try {
            if (i % 100 == 0){
                size_t type, id;
                float x, y, angle;
                _world.createRandomModifier(type, id, x, y, angle);
                std::cout << "Creating modifier in " << x << " " << y;

                for (auto &actualClient : clients) {
                    actualClient.second->createModifier(type, id, x, y, angle);
                }

            }

            std::shared_ptr<SnapshotEvent> snapshot(new SnapshotEvent);
            std::clock_t begin = clock();

            if (!clients.empty()) {
                while (incomingEvents.get(event)) {
                    std::cout << "---Command: " << event->j["cmd_id"].get<int>() << std::endl;
                   clients[event->j["client_id"]]->handleInput((InputEnum) event->j["cmd_id"].get<int>());
                }

                step();

                for (auto &actualClient : clients) {
                    actualClient.second->modifySnapshotFromClient(snapshot);
                }

                for (auto &actualClient : clients) {
                    actualClient.second->sendSnapshot(snapshot);
                }
            }

            i++;

            std::clock_t end = clock();
            double execTime = double(end - begin) / (CLOCKS_PER_SEC / 1000);
            double frames = 30;
            if (execTime < frames) {
                int to_sleep = (frames - execTime);
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(to_sleep));
            }
        } catch (SocketError &se) {
            roomRunning = false;
            std::cerr << se.what();
        } catch (std::exception &e){
            roomRunning = false;
            std::cout << "Excepcion desde game thread: " << std::endl;
        } catch (...) {
            serverRunning = false;
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

void GameThread::startGame() {
    _gameStarted = true;
}
