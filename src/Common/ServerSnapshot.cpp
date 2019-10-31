#include "ServerSnapshot.h"
#include <sstream>
#include "ServerSnapshot.h"
#include "Protocol.h"
#include "json.hpp"

using json = nlohmann::json;


ServerSnapshot::ServerSnapshot(Protocol &protocol) {
    std::string serialized = protocol.receive();
    auto jVec = json::parse(serialized);

    for (auto& actualSerializedCar : jVec) {
        float x = actualSerializedCar["x"];
        float y = actualSerializedCar["y"];
        int angle = actualSerializedCar["angle"];
        int health = actualSerializedCar["health"];
        int id = actualSerializedCar["id"];
        setCar(x, y, angle, health, id);
    }
}

void ServerSnapshot::setCar(float x, float y, int angle, int health, int id) {
	Car car{};
	car.x = x;
	car.y = y;
	car.angle = angle;
    car.health = health;
	car.id = id;
	carList.push_back(car);
}

const CarList& ServerSnapshot::getCars() {
	return carList;
}


void ServerSnapshot::send(Protocol& protocol){
    std::string finalMessage;
    json jVec;

    for (auto& car: carList){
        json j;
        j["x"] = car.x;
        j["y"] = car.y;
        j["angle"] = car.angle;
        j["health"] = car.health;
        j["id"] = car.id;
        jVec.push_back(j);
    }

    finalMessage = jVec.dump();
    protocol.send(finalMessage);
}

