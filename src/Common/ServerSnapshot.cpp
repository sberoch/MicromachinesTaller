#include "ServerSnapshot.h"

void ServerSnapshot::setCar(int x, int y, int angle, int id) {
	std::map<std::string, int> car;
	car.insert(std::make_pair("x", x));
	car.insert(std::make_pair("y", y));
	car.insert(std::make_pair("angle", angle));
	car.insert(std::make_pair("id", id));
	carList.push_back(std::move(car));
}

const CarList& ServerSnapshot::getCars() {
	return carList;
}