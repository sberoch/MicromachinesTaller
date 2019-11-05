//
// Created by alvaro on 4/11/19.
//

#include "EventReceiver.h"
#include "../../Common/Event/EventCreator.h"

EventReceiver::EventReceiver(Protocol &protocol,
                             SafeQueue<std::shared_ptr<Event>> &nonBlockingQueue,
                             bool &keepTalking):
        protocol(protocol),
        receivingNonBlockingQueue(nonBlockingQueue),
        keepTalking(keepTalking){}

void EventReceiver::run() {
    EventCreator creator;
    while(keepTalking) {
        try {
            std::shared_ptr<Event> event(creator.makeEvent(this->protocol.receive()));
            receivingNonBlockingQueue.push(event);
        }
        catch(const std::exception& e) {
            //Habria que avisar de alguna forma la desconexion.
            keepTalking = false;
            printf("Socket cerrado.");
        } catch(...) {
            keepTalking = false;
            printf("Unknown error from thclient");
        }
    }
}

void EventReceiver::joinThread() {
    this->join();
}
