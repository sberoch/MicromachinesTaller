#include "GameThread.h"
#include "../../Common/Socket.h"
#include "../../Common/Protocol.h"
#include "../../Common/InputEnum.h"
#include "../Player.h"
#include "../../Common/SocketError.h"
#include <iostream>

using namespace std::chrono;

GameThread::GameThread(size_t n_of_players, std::shared_ptr<Configuration> configuration) :
                                             _configuration(configuration),
                                             _world(n_of_players, configuration),
                                             _cars(), _track(), _gameToStart(true),
                                             _gameStarted(true),
                                             _gameEnded(false){
                                             //_gameLoop(&GameThread::run, this){
    _world.createTrack(_track);
}

void GameThread::run(){
    try {
        //Creo socket aceptador
        const char *portNumber = "8888";
        Socket acceptSocket = Socket::createAcceptingSocket(portNumber);

        //Acepto 1 cliente -> Despues va a aceptar hasta que no este llena y no pongan empezar
        Socket skt = acceptSocket.accept();
        Player player(std::move(skt), _world.createCar(0));

        //Protocol protocol(std::move(skt));
        while (_gameStarted) {
            //Get initial time
            std::clock_t begin = clock();

            //ServerSnapshot snap;
            //std::string cmd = protocol.receive();
            std::string cmd;
            player.receive(cmd);
            //player.handleInput((InputEnum) cmd[0]);
            player.handleInput(cmd);
            /*
            if (cmd == "a") {
                update(PRESS_NONE, PRESS_LEFT);
            } else if (cmd == "a_stop") {
                update(PRESS_NONE, RELEASE_LEFT);
            } else if (cmd == "d_stop") {
                update(PRESS_NONE, RELEASE_RIGHT);
            } else if (cmd == "w_stop") {
                update(RELEASE_UP, PRESS_NONE);
            } else if (cmd == "s_stop") {
                update(RELEASE_DOWN, PRESS_NONE);
            } else if (cmd == "d") {
                update(PRESS_NONE, PRESS_RIGHT);
            } else if (cmd == "w") {
                update(PRESS_UP, PRESS_NONE);
            } else if (cmd == "s") {
                update(PRESS_DOWN, PRESS_NONE);
            }*/
            /*
            std::vector<Car*> cars = getCars();
            snap.setCar(cars[0]->x(), cars[0]->y(), cars[0]->angle() * RADTODEG, cars[0]->health(), 11);
            snap.send(protocol);
            */
            //Step del world
            _world.step(_configuration->getVelocityIterations(), _configuration->getPositionIterations());

            player.send();
            //Sleep
            std::clock_t end = clock();
            double execTime = double(end - begin) / (CLOCKS_PER_SEC / 1000);
            if (execTime < 25) {
                int to_sleep = (25 - execTime);
                std::this_thread::sleep_for(std::chrono::milliseconds(to_sleep));
            }
        }
    } catch(SocketError& se){
        std::cerr << se.what();
    } catch(...) {
        std::cerr << "Game Thread: UnknownException.\n";
    }
}

void GameThread::join(){
    _gameLoop.join();
}

std::vector<Car*> GameThread::getCars(){
    return _cars;
}

void GameThread::update(Input movInput, Input turnInput){
    for (size_t i=0; i<_cars.size(); ++i){
        _cars[i]->handleInput(movInput, turnInput);
        _cars[i]->update();
    }

    _world.step(_configuration->getVelocityIterations(), _configuration->getPositionIterations());
}

GameThread::~GameThread() {

}
