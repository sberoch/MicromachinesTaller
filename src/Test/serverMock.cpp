#include "../Common/Socket.h"
#include "../Common/Protocol.h"
#include "../Common/ServerSnapshot.h"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {

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
			angle -= 10;
		} else if (cmd == "d") {
			angle += 10;
		} else if (cmd == "w") {
			y -= 0.2;
		}
		snap.setCar(x, y, angle, health, id);
		snap.send(protocol);
	}

	return 0;
}