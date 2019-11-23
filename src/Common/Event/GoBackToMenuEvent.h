//
// Created by alvaro on 23/11/19.
//

#ifndef MICROMACHINES_GOBACKTOMENUEVENT_H
#define MICROMACHINES_GOBACKTOMENUEVENT_H


#include "Event.h"

class GoBackToMenuEvent : public Event {
private:
public:
    GoBackToMenuEvent(int clientId);
    void send(Protocol &protocol) override;
    ~GoBackToMenuEvent() override;
};


#endif //MICROMACHINES_GOBACKTOMENUEVENT_H
