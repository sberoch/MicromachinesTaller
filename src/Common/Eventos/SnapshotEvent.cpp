<<<<<<< Updated upstream:src/Common/ServerSnapshot.cpp
#include "ServerSnapshot.h"
#include <sstream>
#include "ServerSnapshot.h"
#include "Protocol.h"
=======
#include "SnapshotEvent.h"
#include "../Protocol.h"
#include "../json.hpp"
>>>>>>> Stashed changes:src/Common/Eventos/SnapshotEvent.cpp

static std::string toString(int number){
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

static std::string toString(float number){
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

static float toFloat(const std::string& string){
    std::string::size_type sz;
    float number = std::stof (string, &sz);
    return number;
}

static int toInt(const std::string& string){
    std::stringstream ss(string);
    int x = 0;
    ss >> x;
    return x;
}

<<<<<<< Updated upstream:src/Common/ServerSnapshot.cpp
ServerSnapshot::ServerSnapshot(Protocol &protocol) {
    std::string actualCar = protocol.receive();

    std::vector<std::string> cars =
            protocol.splitCommand(actualCar, ',');

    for (auto&& actualStringChar: cars){
        std::vector<std::string> actualAttributes =
                protocol.splitCommand(actualStringChar, ' ');
        float x = toFloat(actualAttributes[0]);
        float y = toFloat(actualAttributes[1]);
        int angle = toInt(actualAttributes[2]);
        int health = toInt(actualAttributes[3]);
        int id = toInt(actualAttributes[4]);
        this->setCar(x, y, angle, health, id);
    }
}

void ServerSnapshot::setCar(float x, float y, int angle, int health, int id) {
	Car car;
	car.x = x;
	car.y = y;
	car.angle = angle;
=======
void SnapshotEvent::send(Protocol& protocol, int id) {
    std::string finalMessage;
    json jVec;

    for (auto& car: carList){
        json j;
        j["type"] = SNAPSHOT;
        j["x"] = car.x;
        j["y"] = car.y;
        j["angle"] = car.angle;
        j["health"] = car.health;
        j["id"] = id;
        jVec.push_back(j);
    }

    finalMessage = jVec.dump();
    protocol.send(finalMessage);
}

void SnapshotEvent::receive(Protocol &protocol) {
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

void SnapshotEvent::setCar(float x, float y, int angle, int health, int id) {
    CarStruct car{};
    car.x = x;
    car.y = y;
    car.angle = angle;
>>>>>>> Stashed changes:src/Common/Eventos/SnapshotEvent.cpp
    car.health = health;
	car.id = id;
	carList.push_back(car);
}

<<<<<<< Updated upstream:src/Common/ServerSnapshot.cpp
const CarList& ServerSnapshot::getCars() {
	return carList;
}

void ServerSnapshot::send(Protocol& protocol){
    std::string finalMessage;

    for (auto&& car: carList){
        finalMessage.append(toString(car.x) + ' ');
        finalMessage.append(toString(car.y) + ' ');
        finalMessage.append(toString(car.angle) + ' ');
        finalMessage.append(toString(car.health) + ' ');
        finalMessage.append(toString(car.id));
    }
    protocol.send(finalMessage);
}
=======
const CarList& SnapshotEvent::getCars() {
    return carList;
}

>>>>>>> Stashed changes:src/Common/Eventos/SnapshotEvent.cpp
