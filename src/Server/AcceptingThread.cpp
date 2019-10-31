//
// Created by alvaro on 30/9/19.
//


#include <future>
#include "AcceptingThread.h"

AcceptingThread::AcceptingThread(Socket &acceptSocket):
        acceptSocket(acceptSocket){}


 void AcceptingThread::run() {
    try {
        std::atomic<bool> running(true);
        while (running) {
            try {
                Socket skt = this->acceptSocket.accept();
                std::cout << "Client connected" << std::endl;
                Protocol newProtocol(std::move(skt));
                std::shared_ptr<ClientThread> newClientThread
                                        (new ClientThread(std::move(newProtocol)));

                roomController.addClient(newClientThread);

            } catch (SocketError &e){
                running = false;
            }
        }
    } catch(const std::exception &e) {
        printf("ERROR from accepting Thread: %s \n", e.what());
    } catch(...) {
        printf("Unknown error from accepting thread.");
    }
}

AcceptingThread::~AcceptingThread(){
}

