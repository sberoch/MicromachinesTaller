//
// Created by alvaro on 1/11/19.
//

#ifndef MICROMACHINES_COMMANDEVENT_H
#define MICROMACHINES_COMMANDEVENT_H


#include "Event.h"
#include "../Common/json.hpp"

enum InputEnum {
    ACCELERATE = 0,
    STOP_ACCELERATING = 1,
    DESACCELERATE = 2,
    STOP_DESACCELERATING = 3,
    TURN_RIGHT = 4,
    STOP_TURNING_RIGHT = 5,
    TURN_LEFT = 6,
    STOP_TURNING_LEFT = 7
};

class CommandEvent: public Event {
public:
    CommandEvent(InputEnum cmd_id, int client_id);
    CommandEvent(json j);
    virtual void send(Protocol &protocol) override;
    virtual ~CommandEvent() = default;
};


#endif //MICROMACHINES_COMMANDEVENT_H
