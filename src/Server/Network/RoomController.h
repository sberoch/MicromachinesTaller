#ifndef MICROMACHINES_ROOMCONTROLLER_H
#define MICROMACHINES_ROOMCONTROLLER_H

#include <list>
#include <unordered_map>
#include <atomic>
#include "LobbyListener.h"
#include "../../Common/Thread.h"
#include "../../Common/SafeQueue.h"
#include "SafeCounter.h"
#include "../../Common/Protocol.h"
#include "../../Common/Event/CommandEvent.h"


class ClientThread;
class Room;

class RoomController {
private:
    std::unordered_map<int, std::shared_ptr<ClientThread>> clientsWithNoRoom;
    std::unordered_map<int, std::shared_ptr<Room>> rooms;
    SafeQueue<std::string> queue;
    SafeCounter roomCounter;
    std::atomic_bool& acceptSocketRunning;
    std::mutex m;
    LobbyListener listener;

public:
    explicit RoomController(std::atomic_bool& running);

   void addRoom();

   void addClient(int clientId, Protocol protocol);

   void addClientToRoom(int roomId, int clientId);

   void stop();

   void handleInput(json j);

   ~RoomController();

    void collectDeadClients();
};


#endif //MICROMACHINES_ROOMCONTROLLER_H
