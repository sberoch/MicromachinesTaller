//
// Created by alvaro on 1/11/19.
//

#ifndef MICROMACHINES_PLAYASBOTEVENT_H
#define MICROMACHINES_PLAYASBOTEVENT_H


#include "Event.h"

class PlayAsBotEvent: public Event{
public:
    void send(Protocol &protocol, int id) override;

    void receive(Protocol &protocol) override {}

    ~PlayAsBotEvent() override;
};


#endif //MICROMACHINES_PLAYASBOTEVENT_H
