//
// Created by alvaro on 4/11/19.
//

#include "EventSender.h"

EventSender::EventSender(Protocol &protocol,
         SafeQueue<std::shared_ptr<Event>> &sendingBlockingQueue,
         std::atomic_bool& acceptSocketRunning):
        protocol(protocol),
        sendingBlockingQueue(sendingBlockingQueue),
        acceptSocketRunning(acceptSocketRunning){}

void EventSender::run() {
    std::cout << "Sending" << std::endl;
    std::shared_ptr<Event> toBeSent;
    try {
        while (acceptSocketRunning) {
            sendingBlockingQueue.pop(toBeSent);
            toBeSent->send(protocol);
        }
    } catch(const std::exception& e) {
        //TODO:Habria que avisar de alguna forma la desconexion.
        acceptSocketRunning = false;
        printf("Socket cerrado.");
    } catch(...) {
        acceptSocketRunning = false;
        printf("Unknown error from thclient");
    }
}

void EventSender::joinThread() {
    this->join();
}
