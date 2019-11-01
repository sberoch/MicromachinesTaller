//
// Created by alvaro on 1/11/19.
//

#ifndef MICROMACHINES_COMMANDEVENT_H
#define MICROMACHINES_COMMANDEVENT_H


#include "Event.h"

enum InputEnum {
    ACCELERATE,
    STOP_ACCELERATING,
    DESACCELERATE,
    STOP_DESACCELERATING,
    TURN_RIGHT, STOP_TURNING_RIGHT, TURN_LEFT, STOP_TURNING_LEFT
};

class CommandEvent: public Event{
public:
    CommandEvent();

    void sendEvent(Protocol &protocol, int id);

    ~CommandEvent();
};


#endif //MICROMACHINES_COMMANDEVENT_H
