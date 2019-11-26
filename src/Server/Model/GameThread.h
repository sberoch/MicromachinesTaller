#ifndef MICROMACHINES_GAMETHREAD_H
#define MICROMACHINES_GAMETHREAD_H

#include <vector>
#include "Car/Car.h"
#include "World.h"
#include "../Network/ThClient.h"
#include <thread>

#include "../ModsThread.h"

class GameThread : public Thread{
private:
    World _world;

    WorldDTO_t _worldDTO;

    std::shared_ptr<Configuration> _configuration;
    std::unordered_map<int, std::shared_ptr<ClientThread>> finishedPlayers;
    std::atomic_bool& acceptSocketRunning;
    std::atomic_bool& roomRunning;
    std::atomic_bool& gameStarted;
    SafeQueue<std::shared_ptr<Event>>& incomingEvents;
    std::unordered_map<int ,std::shared_ptr<ClientThread>>& clients;
    RoomController& controller;
    int roomId;

public:
    GameThread(size_t n_of_players, const std::shared_ptr<Configuration>& configuration,
             std::atomic_bool& acceptSocketRunning,
             std::atomic_bool& roomRunning,
             std::atomic_bool& gameStarted,
             SafeQueue<std::shared_ptr<Event>>& incomingEvents,
             std::unordered_map<int ,std::shared_ptr<ClientThread>>& clients,
             RoomController& controller,
             int roomId);

    void run() override;

    json getSerializedMap();
    std::shared_ptr<Car> createCar(int id, json j);
    void step();

    //Method to apply changes in DTO to model
    void applyPluginChanges();
    void addToFinishedPlayers(
            std::unordered_map<int, std::shared_ptr<ClientThread>> &clients,
            int clientToBeRemovedId);

    ~GameThread() override;

    void handleEvent(const std::shared_ptr<Event>& event);

    void removeDeadClients();

    void checkIfRoomMustBeClosed();

private:

	void createModifiers(ModsThread &modsThread, int step);

	void addPlayerModificationToSnapshot(const std::shared_ptr<SnapshotEvent> &snapshot,
										 const std::shared_ptr<EndSnapshot> &endSnapshot);

	void checkLapCompletion(const std::shared_ptr<SnapshotEvent> &snapshot);

	void eraseFinishedPlayersFromClients();
};

#endif //MICROMACHINES_GAMETHREAD_H
