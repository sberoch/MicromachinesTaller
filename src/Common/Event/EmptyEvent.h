//
// Created by alvaro on 3/11/19.
//

#ifndef MICROMACHINES_EMPTYEVENT_H
#define MICROMACHINES_EMPTYEVENT_H


#include "Event.h"

class EmptyEvent : public Event{
public:
    void send(Protocol& protocol) override;
    ~EmptyEvent() override = default;
};


#endif //MICROMACHINES_EMPTYEVENT_H
