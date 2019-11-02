//
// Created by alvaro on 1/11/19.
//

#ifndef MICROMACHINES_ENTERLOBBYEVENT_H
#define MICROMACHINES_ENTERLOBBYEVENT_H


#include "../Protocol.h"
#include "Event.h"

class EnterLobbyEvent: public Event{
public:
    void send(Protocol &protocol, int id) override;

    void receive(Protocol &protocol) override {}

    ~EnterLobbyEvent() override;
};


#endif //MICROMACHINES_ENTERLOBBYEVENT_H
