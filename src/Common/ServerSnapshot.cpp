#include "ServerSnapshot.h"

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