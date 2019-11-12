//
// Created by alvaro on 4/11/19.
//

#ifndef MICROMACHINES_EVENTRECEIVER_H
#define MICROMACHINES_EVENTRECEIVER_H


#include <memory>
#include <atomic>
#include "../../Common/Protocol.h"
#include "../../Common/Event/Event.h"
#include "../../Common/SafeQueue.h"
#include "../../Common/Thread.h"

class EventReceiver : public Thread{
private:
    Protocol& protocol;
    SafeQueue<std::shared_ptr<Event>>* receivingNonBlockingQueue;
    std::atomic_bool& acceptSocketRunning;
    std::atomic_bool& clientStillTalking;

public:
    EventReceiver(Protocol& protocol, SafeQueue<std::shared_ptr<Event>>* nonBlockingQueue,
                std::atomic_bool& acceptSocketRunning,
                std::atomic_bool& clientStillTalking);
    void run() override;
    void setQueue(SafeQueue<std::shared_ptr<Event>>* receivingNonBlockingQueue);

    void stop();
};


#endif //MICROMACHINES_EVENTRECEIVER_H
