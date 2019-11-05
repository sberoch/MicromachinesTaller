//
// Created by alvaro on 4/11/19.
//

#ifndef MICROMACHINES_EVENTSENDER_H
#define MICROMACHINES_EVENTSENDER_H


#include "../../Common/Thread.h"
#include "../../Common/SafeQueue.h"
#include "../../Common/Event/Event.h"

class EventSender : public Thread {
private:
    SafeQueue<std::shared_ptr<Event>>& sendingBlockingQueue;
    Protocol& protocol;
    bool& keepTalking;

public:
    EventSender(Protocol& protocol, SafeQueue<std::shared_ptr<Event>>& sendingBlockingQueue,
                bool& keepTalking);
    void run() override;
    void joinThread();
};


#endif //MICROMACHINES_EVENTSENDER_H
