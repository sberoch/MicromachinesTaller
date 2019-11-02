//
// Created by alvaro on 1/11/19.
//

#ifndef MICROMACHINES_EVENT_H
#define MICROMACHINES_EVENT_H

#include "../json.hpp"
#include "../Protocol.h"

using json = nlohmann::json;

enum Type{
    COMMAND,
    SNAPSHOT,
    ENTER_LOBBY,
    PLAY_AS_USER,
    PLAY_AS_BOT,
    ENTER_ROOM
};

class Event {
protected:
    json j;
public:
    virtual void send(Protocol& protocol, int id) = 0;

    virtual ~Event() = default;
};


#endif //MICROMACHINES_EVENT_H
