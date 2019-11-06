//
// Created by alvaro on 1/11/19.
//

#ifndef MICROMACHINES_EVENTCREATOR_H
#define MICROMACHINES_EVENTCREATOR_H


#include "Event.h"

class EventCreator {
public:
	//TODO: no se con cual de los dos conviene quedarse
    std::shared_ptr<Event> makeEvent(Protocol& protocol);
    std::shared_ptr<Event> makeEvent(const std::string& recvdEvent);
};


#endif //MICROMACHINES_EVENTCREATOR_H
