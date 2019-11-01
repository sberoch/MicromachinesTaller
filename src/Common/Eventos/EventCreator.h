//
// Created by alvaro on 1/11/19.
//

#ifndef MICROMACHINES_EVENTCREATOR_H
#define MICROMACHINES_EVENTCREATOR_H


#include "Event.h"

class EventCreator {
public:
    static std::shared_ptr<Event> makeEvent(int type);

    virtual void send() = 0;
};


#endif //MICROMACHINES_EVENTCREATOR_H
