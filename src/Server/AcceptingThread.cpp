//
// Created by alvaro on 30/9/19.
//

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
                Thread* newClientThread = new ClientThread(std::move(skt));

                newClientThread->start();
                this->clients.push_back(newClientThread);

                for (auto &&client: clients) {
                    if (client->isDead()) {
                        client->join();
                        delete client;
                        client = nullptr;
                    }
                }
                clients.remove(nullptr);
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
    for (auto &&client: clients){
        client->stop();
        client->join();
        delete client;
    }
}

