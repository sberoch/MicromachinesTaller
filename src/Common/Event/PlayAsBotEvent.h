//
// Created by alvaro on 1/11/19.
//

#ifndef MICROMACHINES_PLAYASBOTEVENT_H
#define MICROMACHINES_PLAYASBOTEVENT_H


#include "Event.h"

class PlayAsBotEvent: public Event{
public:
	PlayAsBotEvent(int id);
    virtual void send(Protocol &protocol) override;
    virtual ~PlayAsBotEvent() = default;
};


#endif //MICROMACHINES_PLAYASBOTEVENT_H
