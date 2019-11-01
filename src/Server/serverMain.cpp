#include "../Common/Socket.h"
#include "../Common/Protocol.h"
#include "../Common/ServerSnapshot.h"
#include <iostream>
#include <string>

#include "Model/Game.h"
#include "Model/Input.h"
#include "Model/Car/Car.h"
#include "json/json.hpp"
#include <vector>
#include <chrono>
#include <thread>

int main(int argc, char const *argv[]) {

	Game game(1);

	//Creo socket aceptador
	const char *portNumber = "8888";
	Socket acceptSocket = Socket::createAcceptingSocket(portNumber);

	//Acepto 1 cliente
	Socket skt = acceptSocket.accept();
	Protocol protocol(std::move(skt));

	//Defino valores iniciales para la posicion del auto
	std::string buffer;
	float x, y;
	int angle, health, id;
	x = 15.0; y = 7.0; angle = 180; health = 100, id = 11;

	//Recibo el comando y devuelvo el cambio de posicion/angulo. (muy basico)
	while(true) {
        std::clock_t begin = clock();
		ServerSnapshot snap;
		std::string cmd = protocol.receive();
		if (cmd == "a") {
			game.update(PRESS_NONE, PRESS_LEFT);

		} else if (cmd == "d") {
			game.update(PRESS_NONE, PRESS_RIGHT);

		} else if (cmd == "w") {
			game.update(PRESS_UP, PRESS_NONE);

		} else if (cmd == "s") {
		    game.update(PRESS_DOWN, PRESS_NONE);
		}
		std::vector<Car*> cars = game.getCars();
		snap.setCar(cars[0]->x(), cars[0]->y(), cars[0]->angle() * RADTODEG, cars[0]->health(), 11);
		snap.send(protocol);

        std::clock_t end = clock();
        double execTime = double(end - begin) / (CLOCKS_PER_SEC/1000);
        if (execTime < 25){
            int to_sleep =  (25 - execTime);
            std::this_thread::sleep_for(std::chrono::milliseconds(to_sleep));
        }


	}

	return 0;
}
