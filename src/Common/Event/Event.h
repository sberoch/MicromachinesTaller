//
// Created by alvaro on 1/11/19.
//

#ifndef MICROMACHINES_EVENT_H
#define MICROMACHINES_EVENT_H

#include "../json.hpp"
#include "../Protocol.h"

using json = nlohmann::json;

enum Type {
    COMMAND = 0,
    GAME_SNAPSHOT = 1,
    ENTER_LOBBY = 2,
    ENTER_ROOM = 3,
    CREATE_ROOM = 4,
    PLAY = 5,
    LOBBY_SNAPSHOT = 6
};

class Event {
public:
    json j;
public:
    virtual void send(Protocol& protocol) = 0;
    virtual ~Event() = default;
};


#endif //MICROMACHINES_EVENT_H
