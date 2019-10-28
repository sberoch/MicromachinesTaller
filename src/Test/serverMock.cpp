#include "../Common/Socket.h"
#include "../Common/Protocol.h"
#include "../Common/ServerSnapshot.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

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
	int angle, id;
	x = 15.0; y = 7.0; angle = 180; id = 11;

	//Recibo el comando y devuelvo el cambio de posicion/angulo. (muy basico)
	while(true) {
		ServerSnapshot snap;
		std::string cmd = protocol.receive();
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		if (cmd == "a") {
			std::cout << "a\n";
			x -= 0.2;
		} else if (cmd == "d") {
			std::cout << "d\n";
			x += 0.2;
		} else if (cmd == "w") {
			std::cout << "w\n";
			y -= 0.2;
		}
		snap.setCar(x, y, angle, id);
		snap.send(protocol);
	}

	return 0;
}