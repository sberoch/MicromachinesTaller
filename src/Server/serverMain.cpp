#include "../Common/Socket.h"
#include "../Common/Protocol.h"
#include "../Common/ServerSnapshot.h"
#include <iostream>
#include <string>

#include "Model/Game.h"
#include "Model/Input.h"
#include "Model/Car/Car.h"
#include <vector>

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
		ServerSnapshot snap;
		std::string cmd = protocol.receive();
		if (cmd == "a") {
			game.update(PRESS_NONE, PRESS_LEFT);

		} else if (cmd == "d") {
			game.update(PRESS_NONE, PRESS_RIGHT);

		} else if (cmd == "w") {
			game.update(PRESS_UP, PRESS_NONE);
		}
		std::vector<Car*> cars = game.getCars();
		snap.setCar(cars[0]->x(), cars[0]->y(), cars[0]->angle(), cars[0]->health(), 11);
		snap.send(protocol);
	}

	return 0;
}