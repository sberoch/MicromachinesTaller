//
// Created by alvaro on 1/11/19.
//

#ifndef MICROMACHINES_ENTERROOMEVENT_H
#define MICROMACHINES_ENTERROOMEVENT_H


#include "Event.h"

class EnterRoomEvent: public Event{
public:
    void send(Protocol &protocol, int id) override;

    void receive(Protocol &protocol) override {}

    ~EnterRoomEvent() override;
};


#endif //MICROMACHINES_ENTERROOMEVENT_H
