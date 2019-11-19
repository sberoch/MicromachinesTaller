#include "GameThread.h"
#include "../../Common/Socket.h"
#include "../../Common/Protocol.h"
#include "../Player.h"
#include "../../Common/SocketError.h"
#include <iostream>
#include "../../Common/Event/EventCreator.h"
#include "../Network/ThClient.h"
#include "../../Common/Event/EndSnapshot.h"

using namespace std::chrono;

GameThread::GameThread(size_t n_of_players, const std::shared_ptr<Configuration>& configuration) :
                                             _configuration(configuration),
                                             _world(n_of_players, configuration),
                                             _gameToStart(true),
                                             _gameStarted(false),
                                             _gameEnded(false){}

void GameThread::run(std::atomic_bool& acceptSocketRunning,
        std::atomic_bool& roomRunning,
        SafeQueue<std::shared_ptr<Event>>& incomingEvents,
        std::unordered_map<int ,std::shared_ptr<ClientThread>>& clients){
    std::shared_ptr<Event> event;

    int i = 0;
    while (roomRunning && acceptSocketRunning) {
        try {
            if (i % _configuration->getModifiersCreationFrequency() == 0){
                size_t type, id;
                float x, y, angle;
                _world.createRandomModifier(type, id, x, y, angle);

                for (auto &actualClient : clients) {
                    actualClient.second->createModifier(type, id, x, y, angle);
                }
            }

            std::shared_ptr<SnapshotEvent> snapshot(new SnapshotEvent);
            std::shared_ptr<EndSnapshot> endSnapshot(new EndSnapshot);
            std::clock_t begin = clock();

            if (!clients.empty()) {
                while (incomingEvents.get(event)) {
                    std::cout << "---Command: " << event->j["cmd_id"].get<int>() << std::endl;
                    int clientId = event->j["client_id"];
                    clients[clientId]->handleInput((InputEnum) event->j["cmd_id"].get<int>());
                }

                for (auto& client: clients){
                    client.second->update();
                }

                step();

                for (auto &actualClient : clients) {
                    actualClient.second->modifySnapshotFromClient(snapshot);
                    if (actualClient.second->finishedPlaying()){
                        std::cout << "Player finished" << std::endl;
                        int clientId = actualClient.first;
                        addToFinishedPlayersAndRemoveFromClients(clients, clientId);
                        endSnapshot->addPlayerFinished(actualClient.second->getIdFromRoom());
                        actualClient.second->sendSnapshot(snapshot);
                    }
                }


                for (auto &actualClient : clients) {
                    actualClient.second->sendSnapshot(snapshot);
                }

                for (auto &actualFinishedPlayer: finishedPlayers){
                    actualFinishedPlayer->sendEndEvent(endSnapshot);
                }
            }

            i++;

            std::clock_t end = clock();
            double execTime = double(end - begin) / (CLOCKS_PER_SEC / 1000);
            double frames = _configuration->getFPS();
            if (execTime < frames) {
                int to_sleep = (frames - execTime);
                std::this_thread::sleep_for(
                        std::chrono::milliseconds(to_sleep));
            }
        } catch (SocketError &se) {
            roomRunning = false;
            std::cout << "SocketErrorFromGameTrhead" << se.what() <<std::endl;
        } catch (std::exception &e){
            roomRunning = false;
            std::cout << "Excepcion desde game thread: " << std::endl;
        } catch (...) {
            roomRunning = false;
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

std::shared_ptr<Car> GameThread::createCar(int id, json j){
    return std::shared_ptr<Car>(_world.createCar(id, j));
}

void GameThread::startGame() {
    _gameStarted = true;
}

void GameThread::addToFinishedPlayersAndRemoveFromClients(
        std::unordered_map<int, std::shared_ptr<ClientThread>> &clients,
        int clientToBeRemovedId) {
    finishedPlayers.push_back(clients.at(clientToBeRemovedId));
    clients.erase(clientToBeRemovedId);
}

