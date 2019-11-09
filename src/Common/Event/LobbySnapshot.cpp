#include "LobbySnapshot.h"
#include <iostream>

/*
-------Example LobbySnapshot json-----
{
  "rooms" : [
    {
      "id": 0,
      "gameStarted": true,
      "players": [
        {
		  "id": 0
        },
        {
		  "id": 1
        },
        {
	      "id": 2
        }
      ]
    },
    {
      "id": 1,
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
            players.push_back(player["id"]);
        }
        addRoom(room["id"], room["gameStarted"], std::move(players));
    }
}

void LobbySnapshot::setPlayerId(int id){
    this->actualClientId = id;
}



void LobbySnapshot::send(Protocol &protocol) {
	std::string finalMessage;
	j.clear();
    for (auto& room : roomsMap) {
        json jRoom;
        jRoom["id"] = room.first;
        jRoom["gameStarted"] = room.second.gameStarted;
        for (auto& player : room.second.players) {
            json jPlayer;
            jPlayer["id"] = player;
            jRoom["players"].push_back(jPlayer);
        }
        j["rooms"].push_back(jRoom);
    }
    finalMessage = j.dump(4);
	std::cout << finalMessage << std::endl;
    protocol.send(finalMessage);
}

void LobbySnapshot::createRoom(int room_id) {
    std::list<int> players; //Null vector
    addRoom(room_id, false, std::move(players));
}

void LobbySnapshot::removePlayerFromAnotherRoom(int player_id){
    for (auto& room: roomsMap){
        auto actualPlayers = room.second.players;
        actualPlayers.remove(player_id);
    }
}

void LobbySnapshot::joinRoom(int player_id, int room_id) {
    if (roomsMap.count(room_id)){
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