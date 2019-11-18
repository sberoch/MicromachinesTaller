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
        addRoom(room["clientId"], room["gameStarted"], std::move(players));
    }
    this->actualClient.clientId = j["player_id"];
    //Esta habria que conseguirla de algun lado.
    //this->actualClient.idInRoom = 0;
}

LobbySnapshot::LobbySnapshot(LobbySnapshot &other) {
    this->roomsMap = other.roomsMap;
}


void LobbySnapshot::setPlayerId(int id){
    this->actualClient.clientId = id;
}

int LobbySnapshot::getMyId() {
    return this->actualClient.clientId;
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
        j["rooms"].push_back(jRoom);
    }
    j["player_id"] = this->actualClient.clientId;
    finalMessage = j.dump(4);
	std::cout << finalMessage << std::endl;
    protocol.send(finalMessage);
}

void LobbySnapshot::createRoom(int room_id) {
    std::list<int> players; //Null vector
    addRoom(room_id, false, std::move(players));
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

void LobbySnapshot::addRoom(int id, bool gameStarted, std::list<int> players) {
    RoomStruct roomStruct {};
    roomStruct.id = id;
    roomStruct.gameStarted = gameStarted;
    roomStruct.players = std::move(players);
    roomsMap.insert(std::make_pair(id, roomStruct));
}

const RoomsMap& LobbySnapshot::getRooms() {
    return roomsMap;
}

bool LobbySnapshot:: gameStarted(int player_id) {
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