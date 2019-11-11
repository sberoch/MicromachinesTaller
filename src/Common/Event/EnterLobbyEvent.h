//
// Created by alvaro on 1/11/19.
//

#ifndef MICROMACHINES_ENTERLOBBYEVENT_H
#define MICROMACHINES_ENTERLOBBYEVENT_H


#include "../Protocol.h"
#include "Event.h"

class EnterLobbyEvent: public Event {
public:
	EnterLobbyEvent();
    virtual void send(Protocol &protocol) override;
    virtual ~EnterLobbyEvent() = default;
};


#endif //MICROMACHINES_ENTERLOBBYEVENT_H
