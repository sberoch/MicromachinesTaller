//
// Created by alvaro on 4/11/19.
//

#include "EventSender.h"
#include "../../Common/SocketError.h"

EventSender::EventSender(Protocol &protocol,
         SafeQueue<std::shared_ptr<Event>> &sendingBlockingQueue,
         std::atomic_bool& acceptSocketRunning,
         std::atomic_bool& clientStillTalking):
        protocol(protocol),
        sendingBlockingQueue(sendingBlockingQueue),
        acceptSocketRunning(acceptSocketRunning),
        clientStillTalking(clientStillTalking){}

void EventSender::run() {
    std::cout << "Sender started." << std::endl;
    std::shared_ptr<Event> toBeSent;
    try {
        while (acceptSocketRunning && clientStillTalking) {
            try {
                sendingBlockingQueue.pop(toBeSent);
                if (toBeSent == nullptr)
                    clientStillTalking = false;
                toBeSent->send(protocol);
            } catch (const SocketError &e) {
                clientStillTalking = false;
                std::cout << "Socket error from event sender" << std::endl;
            }
        }
    } catch(const std::exception& e) {
        //TODO:Habria que avisar de alguna forma la desconexion.
        clientStillTalking = false;
        printf("Socket cerrado.");
    } catch(...) {
        clientStillTalking = false;
        printf("Unknown error from thclient");
    }
}

void EventSender::stop() {
    clientStillTalking = false;
}
