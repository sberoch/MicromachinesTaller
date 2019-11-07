//
// Created by alvaro on 4/11/19.
//

#include "EventReceiver.h"
#include "../../Common/Event/EventCreator.h"

EventReceiver::EventReceiver(Protocol &protocol,
                             SafeQueue<std::shared_ptr<Event>> *nonBlockingQueue,
                             std::atomic_bool &acceptSocketRunning):
        protocol(protocol),
        receivingNonBlockingQueue(nonBlockingQueue),
        acceptSocketRunning(acceptSocketRunning){}

void EventReceiver::run() {
    EventCreator creator;
    while(acceptSocketRunning) {
        try {
            std::cout << "Receiving" << std::endl;
            std::string recvEvent = protocol.receive();
            std::cout << "Received: " << recvEvent << std::endl;
            if (!recvEvent.empty()){
                std::shared_ptr<Event> event(creator.makeEvent(recvEvent));
                receivingNonBlockingQueue->push(event);
            }
        }
        catch(const std::exception& e) {
            //Habria que avisar de alguna forma la desconexion.
            acceptSocketRunning = false;
            printf("Socket cerrado: %s \n.", e.what());
        } catch(...) {
            acceptSocketRunning = false;
            printf("Unknown error from thclient \n");
        }
    }
}

void EventReceiver::joinThread() {
    this->join();
}

void EventReceiver::setQueue(SafeQueue<std::shared_ptr<Event>>* receivingNonBlockingQueue) {
    this->receivingNonBlockingQueue = receivingNonBlockingQueue;
}
