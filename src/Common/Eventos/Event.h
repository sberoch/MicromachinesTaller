//
// Created by alvaro on 1/11/19.
//

#ifndef MICROMACHINES_EVENT_H
#define MICROMACHINES_EVENT_H

#include "../json.hpp"
#include "../Protocol.h"

using json = nlohmann::json;

class Event {
protected:
    json j;
public:
    Event();

    void sendEvent(Protocol& protocol, int id);


    ~Event();
};


#endif //MICROMACHINES_EVENT_H
