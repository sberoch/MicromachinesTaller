//
// Created by alvaro on 30/9/19.
//


#include <future>
#include "AcceptingThread.h"
#include "../../Common/Protocol.h"
#include "../../Common/SocketError.h"

AcceptingThread::AcceptingThread(Socket &acceptSocket):
        acceptSocket(acceptSocket), running(true), roomController(running){}


 void AcceptingThread::run() {
    std::cout << "Starting acceptor" << std::endl;
    try {
        while (running) {
            try {
                Protocol newProtocol(this->acceptSocket.accept());
                std::cout << "Client connected" << std::endl;
                int clientId = clientCounter.returnAndAddOne();

                roomController.addClient(clientId, std::move(newProtocol));
            } catch (SocketError &e){
                running = false;
                roomController.stop();
            }
        }
    } catch(const std::exception &e) {
        printf("ERROR from accepting Thread: %s \n", e.what());
    } catch(...) {
        printf("Unknown error from accepting thread.");
    }
}

AcceptingThread::~AcceptingThread(){
    roomController.stop();
}

