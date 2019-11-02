//
// Created by alvaro on 1/11/19.
//

#include "CommandEvent.h"
#include "EventCreator.h"
#include <memory>
#include "../Constants.h"

//TODO:Faltan crear los eventos.
std::shared_ptr<Event> EventCreator::makeEvent(int type){
    if (type == COMMAND)
        return std::shared_ptr<Event>(new CommandEvent);
    else if (type == SNAPSHOT)
        return std::shared_ptr<Event>(new CommandEvent);
    else if (type == ENTER_LOBBY)
        return std::shared_ptr<Event>(new CommandEvent);
    else if (type == PLAY_AS_USER)
        return std::shared_ptr<Event>(new CommandEvent);
    else if (type == PLAY_AS_BOT)
        return std::shared_ptr<Event>(new CommandEvent);
    else if (type == ENTER_ROOM)
        return std::shared_ptr<Event>(new CommandEvent);

}