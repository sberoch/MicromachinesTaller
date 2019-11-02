//
// Created by alvaro on 1/11/19.
//

#ifndef MICROMACHINES_PLAYASUSEREVENT_H
#define MICROMACHINES_PLAYASUSEREVENT_H


#include "Event.h"

class PlayAsUserEvent: public Event{
public:
    void send(Protocol &protocol, int id) override;

    void receive(Protocol &protocol) override {}

    ~PlayAsUserEvent() override;
};


#endif //MICROMACHINES_PLAYASUSEREVENT_H
