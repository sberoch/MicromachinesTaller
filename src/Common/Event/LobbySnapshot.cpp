#include "LobbySnapshot.h"
#include <iostream>
#include <algorithm>

/*
-------Example LobbySnapshot json-----
{
  "rooms" : [
    {
      "clientId": 0,
      "gameStarted": true,
      "players": [
        {
		  "clientId": 0
        },
        {
		  "clientId": 1
        },
        {
	      "clientId": 2
        }
      ]
    },
    {
      "clientId": 1,
      "gameStarted": false
    }
  ],
}
*/

LobbySnapshot::LobbySnapshot(Protocol& protocol) {
    std::string serialized = protocol.receive();
    this->j = json::parse(serialized);

    for (auto& room : j["rooms"]) {
        std::list<int> players;
        for (auto& player : room["players"]) {
            players.push_back(player["clientId"]);
        }
        std::vector<bool> selectedCars;
        for(unsigned i = 0; i < 4; ++i) {
            for (auto& selected : room["selectedCars"]) {
                selectedCars.push_back(selected["selected"]);
            }
        }
        addRoom(room["clientId"], room["gameStarted"],
                std::move(players), std::move(selectedCars));
    }
    this->actualClientId = j["player_id"];
}

LobbySnapshot::LobbySnapshot(LobbySnapshot &other) {
    this->roomsMap = other.roomsMap;
}

void LobbySnapshot::setPlayerId(int id){
    this->actualClientId = id;
}

int LobbySnapshot::getMyId() {
    return this->actualClientId;
}

void LobbySnapshot::send(Protocol &protocol) {
    std::string finalMessage;
    j.clear();
    for (auto& room : roomsMap) {
        json jRoom;
        jRoom["clientId"] = room.first;
        jRoom["gameStarted"] = room.second.gameStarted;
        for (auto& player : room.second.players) {
            json jPlayer;
            jPlayer["clientId"] = player;
            jRoom["players"].push_back(jPlayer);
        }
        for(unsigned i = 0; i < 4; ++i) {
            json jSelectedCar;
            jSelectedCar["selected"] = (bool) room.second.selectedCars.at(i);
            jRoom["selectedCars"].push_back(jSelectedCar);
        }
        j["rooms"].push_back(jRoom);
    }
    j["player_id"] = this->actualClientId;
    finalMessage = j.dump(4);
    std::cout << finalMessage << std::endl;
    protocol.send(finalMessage);
}

void LobbySnapshot::createRoom(int room_id) {
    std::list<int> players; //Null vector
    std::vector<bool> selectedCars = {false, false, false, false};
    addRoom(room_id, false,
            std::move(players), std::move(selectedCars));
}


void LobbySnapshot::removeIdFromOldRoom(int player_id){
    for (auto& actualRoom: roomsMap){
        actualRoom.second.players.remove(player_id);
    }
}

void LobbySnapshot::joinRoom(int player_id, int room_id) {
    if (roomsMap.count(room_id)){
        removeIdFromOldRoom(player_id);
        roomsMap.at(room_id).players.push_back(player_id);
    }
}
void LobbySnapshot::startGame(int room_id) {
    roomsMap.at(room_id).gameStarted = true;
}

void LobbySnapshot::addRoom(int id, bool gameStarted,
                            std::list<int> players, std::vector<bool> selectedCars) {
    RoomStruct roomStruct {};
    roomStruct.id = id;
    roomStruct.gameStarted = gameStarted;
    roomStruct.players = std::move(players);
    roomStruct.selectedCars = std::move(selectedCars);
    roomsMap.insert(std::make_pair(id, roomStruct));
}

void LobbySnapshot::addSelectedCar(int room_id, int player_room_id) {
    roomsMap.at(room_id).selectedCars[player_room_id] = true;
}

void LobbySnapshot::removeSelectedCar(int room_id, int player_room_id) {
    roomsMap.at(room_id).selectedCars[player_room_id] = false;
}

const RoomsMap& LobbySnapshot::getRooms() {
    return roomsMap;
}

bool LobbySnapshot::gameStarted(int player_id) {
    for (auto& room : roomsMap) {
        if (room.second.gameStarted) {
            for (auto& player : room.second.players) {
                if (player == player_id) {
                    return true;
                }
            }
        }
    }
    return false;
}