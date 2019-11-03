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
    explicit CommandEvent(InputEnum cmd_id);
    explicit CommandEvent(json j);
    void send(Protocol &protocol) override;
    ~CommandEvent() override = default;
};


#endif //MICROMACHINES_COMMANDEVENT_H
