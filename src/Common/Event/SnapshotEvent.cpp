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

    for (auto& car: carList){
        json jCar;
        jCar["x"] = car.x;
        jCar["y"] = car.y;
        jCar["angle"] = car.angle;
        jCar["health"] = car.health;
        jCar["id"] = car.id;

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
    CarStruct car{};
    car.x = x;
    car.y = y;
    car.angle = angle;
    car.health = health;
    car.id = id;
    carList.push_back(car);
}

const CarList& SnapshotEvent::getCars() {
    return carList;
}

void SnapshotEvent::addStraightTrack(float x, float y, int angle, int id) {    
    setGameEvent(ADD, TYPE_STRAIGHT_TRACK, x, y, angle, id);
}

void SnapshotEvent::addCurveTrack(float x, float y, int angle, int id) {
    setGameEvent(ADD, TYPE_CURVE_TRACK, x, y, angle, id);
}

void SnapshotEvent::addRock(float x, float y, int id) {
    setGameEvent(ADD, TYPE_ROCK, x, y, 0, id);
}

void SnapshotEvent::addOil(float x, float y, int angle, int id) {
    setGameEvent(ADD, TYPE_OIL, x, y, angle, id);
}

void SnapshotEvent::addMud(float x, float y, int angle, int id) {
    setGameEvent(ADD, TYPE_MUD, x, y, angle, id);
}

void SnapshotEvent::addHealthPowerup(float x, float y, int id) {
    setGameEvent(ADD, TYPE_HEALTH_POWERUP, x, y, 0, id);
}

void SnapshotEvent::addBoostPowerup(float x, float y, int id) {
    setGameEvent(ADD, TYPE_BOOST_POWERUP, x, y, 0, id);
}

void SnapshotEvent::addExplosion(float x, float y) {
    setGameEvent(ADD, TYPE_EXPLOSION, x, y, 0, 0);
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

const GameEventsList& SnapshotEvent::getGameEvents() {
    return gameEventsList;
}
