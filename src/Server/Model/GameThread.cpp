#include "GameThread.h"
#include "../../Common/Socket.h"
#include "../../Common/Protocol.h"
#include "../Player.h"
#include "../../Common/SocketError.h"
#include <iostream>
#include <utility>
#include "../../Common/Event/EventCreator.h"

using namespace std::chrono;

GameThread::GameThread(size_t n_of_players, std::shared_ptr<Configuration> configuration) :
                                              _configuration(configuration),
                                              _world(n_of_players, configuration),
                                              _gameToStart(true),
                                              _gameStarted(true),
                                              _gameEnded(false){
                                              //_gameLoop(&GameThread::run, this){
                                              }

void GameThread::run(){
    try {
        //Creo socket aceptador
        const char *portNumber = "8888";
        Socket acceptSocket = Socket::createAcceptingSocket(portNumber);

        //Acepto 1 cliente -> Despues va a aceptar hasta que no este llena y no pongan empezar
        Socket skt = acceptSocket.accept();
        Player player(std::move(skt), _world.createCar(1), 0);

        player.sendStart(_world.getSerializedMap()); //TODO: mover donde corresponda

        Socket skt2 = acceptSocket.accept();
        Player player2(std::move(skt2), _world.createCar(1), 1);

        int i = 0;
        EventCreator eventCreator; 
        while (_gameStarted) {
            //Get initial time
            std::clock_t begin = clock();

            std::string cmd;
            player.receive(cmd);
            
            std::shared_ptr<Event> event = eventCreator.makeEvent(cmd);
            player.handleInput((InputEnum) event->j["cmd_id"].get<int>());

            //Step del world
            _world.step(_configuration->getVelocityIterations(), _configuration->getPositionIterations());

            player.send();

            ++i;
            if (i % 50 == 0){
                size_t type, id;
                float x, y, angle;
                _world.createRandomModifier(type, id, x, y, angle);
                std::cout << "Creating modifier in " << x << " " << y;
                player.createModifier(type, id, x, y, angle);
            }

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

GameThread::~GameThread() {}
