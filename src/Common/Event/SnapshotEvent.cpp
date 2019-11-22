#include "SnapshotEvent.h"
#include "../Constants.h"
#include <iostream>

using json = nlohmann::json;

/*
-------Example SnapshotEvent json-----
{
  "cars" : [
    {
      "x": 15,
      "y": 10,
      "angle": 90,
      "health" : 100,
      "clientId": 1
    }
  ],
  "events" : [
    {
      "event_type": 0, (ADD, ver enum en SnapshotEvent.h)
      "object_type": 113 (ID_EXPLOSION, ver en Constants.h)
      "x": 15,
      "y": 9,
      "angle": 0
      "clientId": 1
    }
  ]
}
*/

SnapshotEvent::SnapshotEvent(Protocol &protocol) {
    std::string serialized = protocol.receive();
    this->j = json::parse(serialized);

    std::cout << serialized << std::endl;

    for (auto& car : j["cars"]) {
        setCar(car["x"],
               car["y"],
               car["angle"],
               car["health"],
               car["clientId"]);
    }

    for (auto& gameEvent : j["events"]) {
        setGameEvent(gameEvent["eventType"],
                    gameEvent["objectType"],
                    gameEvent["x"],
                    gameEvent["y"],
                    gameEvent["angle"],
                    gameEvent["clientId"]);
    }
}

void SnapshotEvent::send(Protocol& protocol) {
    std::string finalMessage;

    for (auto& car: carStructList){
        json jCar;
        jCar["x"] = car.x;
        jCar["y"] = car.y;
        jCar["angle"] = car.angle;
        jCar["health"] = car.health;
        jCar["clientId"] = car.id;

        j["cars"].push_back(jCar);
    }

    for (auto& gameEvent : gameEventsList) {
        json jGameEvent;
        jGameEvent["eventType"] = gameEvent.eventType;
        jGameEvent["objectType"] = gameEvent.objectType;
        jGameEvent["x"] = gameEvent.x;
        jGameEvent["y"] = gameEvent.y;
        jGameEvent["angle"] = gameEvent.angle;
        jGameEvent["clientId"] = gameEvent.id;

        j["events"].push_back(jGameEvent);
    }

    finalMessage = j.dump(4);
    protocol.send(finalMessage);
}

bool SnapshotEvent::isThereACar(int id){
    for (auto& actualCar: carStructList){
        if (actualCar.id == id){
            return true;
        }
    }
    return false;
}

CarStruct SnapshotEvent::findCar(int id){
    for (auto& actualCar: carStructList){
        if (actualCar.id == id){
            return actualCar;
        }
    }
}

void SnapshotEvent::setCar(float x, float y, int angle, int health, int id) {
    bool found = this->isThereACar(id);
    if (found){
        CarStruct actualCar = findCar(id);
        actualCar.x = x;
        actualCar.y = y;
        actualCar.angle = angle;
        actualCar.health = health;
        actualCar.id = id;
    } else {
        CarStruct car{};
        car.x = x;
        car.y = y;
        car.angle = angle;
        car.health = health;
        car.id = id;
        carStructList.push_back(car);
    }
}

const CarStructList& SnapshotEvent::getCars() {
    return carStructList;
}

void SnapshotEvent::addGameItem(int type, float x, float y, int angle, int id) {    
    setGameEvent(ADD, type, x, y, angle, id);
}

void SnapshotEvent::removeGameItem(int type, int id) {
    setGameEvent(REMOVE, type, 0, 0, 0, id);  
}

void SnapshotEvent::signalMapReady() {
    setGameEvent(MAP_LOAD_FINISHED, 0, 0, 0, 0, 0);
}

void SnapshotEvent::setGameOver(int inRoomId) {
    setGameEvent(GAME_OVER, 0, 0, 0, 0, inRoomId);
}

void SnapshotEvent::setMudSplatEvent() {
    setGameEvent(MUD_SPLAT, 0, 0, 0, 0, 0);
}

void SnapshotEvent::setGameEvent(SnapshotGameEventType eventType,
            int objectType, float x, float y, int angle, int id) {
    GameEventStruct gameEvent{};
    gameEvent.eventType = eventType;
    gameEvent.objectType = objectType;
    gameEvent.x = x;
    gameEvent.y = y;
    gameEvent.angle = angle;
    gameEvent.id = id;
    gameEventsList.push_back(gameEvent);
}

void SnapshotEvent::setMap(const json& jMap) {
	//TODO: esto del clientId deberia venir de afuera
	std::cout << "Sending map\n";
	for (auto& car : jMap["cars"]) {
        setGameEvent(ADD, 
        			car["color"],
        			car["x_init"],
               		car["y_init"],
               		car["angle"],
               		car["id_from_room"]);
    }
    int id = 0;
    for (auto& track : jMap["tracks"])  {
    	setGameEvent(ADD,
    				track["type"],
    				track["x"],
               		track["y"],
               		track["angle"],
               		id);
    	id++;
    }
    
    json jStart = jMap["startLine"];
    setGameEvent(ADD, 
                jStart["type"],
                jStart["x"],
                jStart["y"],
                jStart["angle"],
                0);
}

const GameEventsList& SnapshotEvent::getGameEvents() {
    return gameEventsList;
}

SnapshotEvent::SnapshotEvent(SnapshotEvent &other) {
    this->carStructList = other.carStructList;
    this->gameEventsList = other.gameEventsList;
}

void SnapshotEvent::setLapNumber(int clientIdFromRoom, int lapNumber) {
	setGameEvent(LAP_COMPLETED, 0, 0, 0, lapNumber, clientIdFromRoom);
}

