//
// Created by alvaro on 4/11/19.
//

#include "EventReceiver.h"
#include "../../Common/Event/EventCreator.h"
#include "../../Common/SocketError.h"

EventReceiver::EventReceiver(Protocol &protocol,
                             SafeQueue<std::shared_ptr<Event>> *nonBlockingQueue,
                             std::atomic_bool& acceptSocketRunning,
                             std::atomic_bool& clientStillTalking):
                            protocol(protocol),
                            receivingNonBlockingQueue(nonBlockingQueue),
                            acceptSocketRunning(acceptSocketRunning),
                            clientStillTalking(clientStillTalking){}

void EventReceiver::run() {
    EventCreator creator;
    while(acceptSocketRunning && clientStillTalking) {
        try {
            std::string recvEvent = protocol.receive();
            if (!recvEvent.empty()){
                std::shared_ptr<Event> event(creator.makeEvent(recvEvent));
                receivingNonBlockingQueue->push(event);
            }
        } catch(const SocketError &e){
            clientStillTalking = false;
            std::cout << "Socket error from event receiver" << std::endl;
        } catch(const std::exception& e) {
            //Habria que avisar de alguna forma la desconexion.
            clientStillTalking = false;
            printf("Socket cerrado: %s \n.", e.what());
        } catch(...) {
            clientStillTalking = false;
            printf("Unknown error from thclient \n");
        }
    }
}

void EventReceiver::setQueue(SafeQueue<std::shared_ptr<Event>>* receivingNonBlockingQueue) {
    this->receivingNonBlockingQueue = receivingNonBlockingQueue;
}

void EventReceiver::stop() {
    clientStillTalking = false;
}
