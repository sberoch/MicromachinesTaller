//
// Created by alvaro on 4/11/19.
//

#include "EventSender.h"

EventSender::EventSender(Protocol &protocol,
         SafeQueue<std::shared_ptr<Event>> &sendingBlockingQueue,
         bool &keepTalking):
        protocol(protocol),
        sendingBlockingQueue(sendingBlockingQueue),
        keepTalking(keepTalking){}

void EventSender::run() {
    std::shared_ptr<Event> toBeSent;
    try {
        while (keepTalking) {
            sendingBlockingQueue.pop(toBeSent);
            toBeSent->send(protocol);
        }
    } catch(const std::exception& e) {
        //TODO:Habria que avisar de alguna forma la desconexion.
        keepTalking = false;
        printf("Socket cerrado.");
    } catch(...) {
        keepTalking = false;
        printf("Unknown error from thclient");
    }
}

void EventSender::joinThread() {
    this->join();
}
