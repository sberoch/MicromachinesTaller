#include "../Common/Socket.h"
#include "../Common/Protocol.h"
#include "../Common/ServerSnapshot.h"
#include <iostream>
#include <string>

#include "Model/Configuration.h"
#include "Model/GameThread.h"
#include "Model/Input.h"
#include "Model/Car/Car.h"
#include <vector>
#include <chrono>
#include <thread>

int main(int argc, char const *argv[]) {
    try {
        std::shared_ptr<Configuration> configuration(std::make_shared<Configuration>());
        GameThread game(1, configuration);

        game.run();
        game.join();
    } catch (const std::exception &e) {
        printf("ERROR: %s", e.what());
        
    } catch (...) {
        std::cout << "Server UnknownException.\n";
    }

	/*
	//Creo socket aceptador
	const char *portNumber = "8888";
	Socket acceptSocket = Socket::createAcceptingSocket(portNumber);*/

	/*
	//Acepto 1 cliente
	Socket skt = acceptSocket.accept();
	Protocol protocol(std::move(skt));*/
    /*
	//Recibo el comando y devuelvo el cambio de posicion/angulo. (muy basico)
	while(true) {
        std::clock_t begin = clock();
		ServerSnapshot snap;
		std::string cmd = protocol.receive();
		if (cmd == "a") {
			game.update(PRESS_NONE, PRESS_LEFT);
		} else if (cmd == "a_stop") {
            game.update(PRESS_NONE, RELEASE_LEFT);
		} else if (cmd == "d_stop") {
            game.update(PRESS_NONE, RELEASE_RIGHT);
		} else if (cmd == "w_stop") {
            game.update(RELEASE_UP, PRESS_NONE);
		} else if (cmd == "s_stop") {
            game.update(RELEASE_DOWN, PRESS_NONE);
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


	}*/


	return 0;
}