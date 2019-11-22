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

GameThread::GameThread(size_t n_of_players, 
                    const std::shared_ptr<Configuration>& configuration,
                    std::atomic_bool& acceptSocketRunning,
                    std::atomic_bool& roomRunning,
                    SafeQueue<std::shared_ptr<Event>>& incomingEvents,
                    std::unordered_map<int ,std::shared_ptr<ClientThread>>& clients) :
                                             _configuration(configuration),
                                             _world(n_of_players, configuration),
                                             _worldDTO(),
                                             acceptSocketRunning(acceptSocketRunning),
                                             roomRunning(roomRunning),
                                             incomingEvents(incomingEvents),
                                             clients(clients) {

}

void GameThread::run() {
    std::cout << "Running GameThread" << std::endl;
    ModsThread modsThread("libs.txt", &_worldDTO);
    gameStarted = true;
    std::shared_ptr<Event> event;
    std::shared_ptr<EndSnapshot> endSnapshot(new EndSnapshot);

    int i = 0;
    while (roomRunning && acceptSocketRunning) {
        try {
            std::shared_ptr<SnapshotEvent> snapshot(new SnapshotEvent);
            std::clock_t begin = clock();

            while (incomingEvents.get(event)) {
                std::cout << "---Command: " << event->j["cmd_id"].get<int>() << std::endl;
                int clientId = event->j["client_id"];
                clients.at(clientId)->handleInput((InputEnum) event->j["cmd_id"].get<int>());
            }

            for (auto& client: clients){
                client.second->update();
            }

            step();

            //MODS CODE
            //TODO refactor
            if ((i % _configuration->getModifiersCreationFrequency()) == 0){
                modsThread.run();
                applyPluginChanges();

                for (size_t i=0; i<MAX_MODIFIERS; ++i){
                    ModifierDTO modifier = _worldDTO.modifiers[i];
                    if (modifier.newModifier){
                        _worldDTO.modifiers[i].newModifier = false;
                        for (auto &actualClient : clients) {
                            actualClient.second->createModifier(modifier.type, modifier.id, modifier.x, modifier.y, modifier.angle);
                        }
                    }
                }
            }

            for (auto &actualClient : clients) {
                actualClient.second->modifySnapshotFromClient(snapshot);
                if (actualClient.second->finishedPlaying()){
                    std::cout << "Player finished" << std::endl;
                    int clientId = actualClient.first;
                    actualClient.second->sendSnapshot(snapshot);
                    addToFinishedPlayers(clients, clientId);
                    endSnapshot->addPlayerFinished(actualClient.second->getIdFromRoom());
                }
            }

            for (auto& actualFinishedPlayer: finishedPlayers){
                if (clients.count(actualFinishedPlayer->getClientId()))
                    clients.erase(actualFinishedPlayer->getClientId());
            }

            for (auto &actualClient : clients) {
                actualClient.second->sendSnapshot(snapshot);
            }


            for (auto &actualFinishedPlayer: finishedPlayers) {
                actualFinishedPlayer->sendEndEvent(endSnapshot);
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
    std::cout << "GameThread ready to be joined" << std::endl;
}

void GameThread::step(){
    _world.step(_configuration->getVelocityIterations(), _configuration->getPositionIterations());
    _world.toDTO(&_worldDTO);
}

void GameThread::applyPluginChanges() {
    _world.dtoToModel(&_worldDTO);
}


json GameThread::getSerializedMap() {
    return _world.getSerializedMap();
}

std::shared_ptr<Car> GameThread::createCar(int id, json j){
    return std::shared_ptr<Car>(_world.createCar(id, j));
}

void GameThread::addToFinishedPlayers(
        std::unordered_map<int, std::shared_ptr<ClientThread>> &clients,
        int clientToBeRemovedId) {
    finishedPlayers.push_back(clients.at(clientToBeRemovedId));
}


GameThread::~GameThread() = default;

