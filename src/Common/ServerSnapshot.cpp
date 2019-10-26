#include <sstream>
#include "ServerSnapshot.h"
#include "Protocol.h"

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
        int id = toInt(actualAttributes[3]);
        this->setCar(x, y, angle, id);
    }
}

void ServerSnapshot::setCar(float x, float y, int angle, int id) {
	Car car;
	car.x = x;
	car.y = y;
	car.angle = angle;
	car.id = id;
	carList.push_back(car);
}

const CarList& ServerSnapshot::getCars() {
	return carList;
}

void ServerSnapshot::send(Protocol& protocol){
    std::string finalMessage;

    for (auto&& car: carList){
        finalMessage.append(toString(car.x) + ' ');
        finalMessage.append(toString(car.y) + ' ');
        finalMessage.append(toString(car.angle) + ' ');
        finalMessage.append(toString(car.id));
    }
    protocol.send(finalMessage);
}
