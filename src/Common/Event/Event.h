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
    PLAY_AS_USER = 3,
    PLAY_AS_BOT = 4,
    ENTER_ROOM = 5,
    CREATE_ROOM = 6,
    PLAY = 7, 
    LOBBY_SNAPSHOT = 8
};

class Event {
public:
    json j;
public:
    virtual void send(Protocol& protocol) = 0;
    virtual ~Event() = default;
};


#endif //MICROMACHINES_EVENT_H
