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
      "id": 1
    }
  ],
  "events" : [
    {
      "event_type": 0, (ADD, ver enum en SnapshotEvent.h)
      "object_type": 113 (ID_EXPLOSION, ver en Constants.h)
      "x": 15,
      "y": 9,
      "angle": 0
      "id": 1
    }
  ]
}
*/

SnapshotEvent::SnapshotEvent(Protocol &protocol) {
    std::string serialized = protocol.receive();
    this->j = json::parse(serialized);

    for (auto& car : j["cars"]) {
        setCar(car["x"],
               car["y"],
               car["angle"],
               car["health"],
               car["id"]);
    }

    for (auto& gameEvent : j["events"]) {
        setGameEvent(gameEvent["eventType"],
                    gameEvent["objectType"],
                    gameEvent["x"],
                    gameEvent["y"],
                    gameEvent["angle"],
                    gameEvent["id"]);
    }
}

void SnapshotEvent::send(Protocol& protocol) {
    std::string finalMessage;
    j.clear();

    for (auto& car: carStructsMap){
        json jCar;
        jCar["x"] = car.second.x;
        jCar["y"] = car.second.y;
        jCar["angle"] = car.second.angle;
        jCar["health"] = car.second.health;
        jCar["id"] = car.second.id;

        j["cars"].push_back(jCar);
    }

    for (auto& gameEvent : gameEventsList) {
        json jGameEvent;
        jGameEvent["eventType"] = gameEvent.eventType;
        jGameEvent["objectType"] = gameEvent.objectType;
        jGameEvent["x"] = gameEvent.x;
        jGameEvent["y"] = gameEvent.y;
        jGameEvent["angle"] = gameEvent.angle;
        jGameEvent["id"] = gameEvent.id;

        j["events"].push_back(jGameEvent);
    }

    finalMessage = j.dump(4);
    std::cout << finalMessage << std::endl;
    protocol.send(finalMessage);
}

void SnapshotEvent::setCar(float x, float y, int angle, int health, int id) {
    if (carStructsMap.count(id)){
        auto actualCar = carStructsMap.at(id);
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
        carStructsMap.insert({car.id, car});
    }
}

const CarStructsMap& SnapshotEvent::getCars() {
    return carStructsMap;
}

void SnapshotEvent::addGameItem(int type, float x, float y, int angle, int id) {    
    setGameEvent(ADD, type, x, y, angle, id);
}

//TODO: por no pasar id nuevo por cada explosion se dibuja una sola vez
//      por un tema con los mapas en GameObjects.cpp



void SnapshotEvent::removeGameItem(int type, int id) {
    setGameEvent(REMOVE, type, 0, 0, 0, id);  
}

void SnapshotEvent::setPlayerId(int id) {
    setGameEvent(ID_ASSIGN, 0, 0, 0, 0, id);
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
	//TODO: esto del id deberia venir de afuera
	std::cout << "Sending map\n";
	int id = 0;
	for (auto& car : jMap["cars"]) {
        setGameEvent(ADD, 
        			car["color"],
        			car["x_init"],
               		car["y_init"],
               		car["angle"],
               		id);
        id++;
    }
    id = 0;
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
    std::cout << jStart.dump(4) << std::endl;
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

