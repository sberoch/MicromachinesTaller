//
// Created by alvaro on 1/11/19.
//

#include "CommandEvent.h"
#include "EventCreator.h"
#include <memory>
#include <iostream>

//TODO:Faltan crear los eventos.
std::shared_ptr<Event> EventCreator::makeEvent(Protocol& protocol){
    std::string recvd = protocol.receive();
    auto j = json::parse(recvd);
    int type = j["type"].get<int>();
    if (type == COMMAND)
        return std::shared_ptr<Event>(new CommandEvent(j));
    else 
        throw std::runtime_error("Wrong event type");
    /*else if (type == EVENT_SNAPSHOT)
        return std::shared_ptr<Event>(new CommandEvent);
    else if (type == EVENT_ENTER_LOBBY)
        return std::shared_ptr<Event>(new CommandEvent);
    else if (type == EVENT_PLAY_AS_USER)
        return std::shared_ptr<Event>(new CommandEvent);
    else if (type == EVENT_PLAY_AS_BOT)
        return std::shared_ptr<Event>(new CommandEvent);
    else if (type == EVENT_ENTER_ROOM)
        return std::shared_ptr<Event>(new CommandEvent);*/
}

//TODO:Faltan crear los eventos.
std::shared_ptr<Event> EventCreator::makeEvent(const std::string& recvdEvent){
    auto j = json::parse(recvdEvent);
    Type type = (Type) j["type"].get<int>();
    if (type == COMMAND)
        return std::shared_ptr<Event>(new CommandEvent(j));
    else 
        throw std::runtime_error("Wrong event type");
    /*else if (type == EVENT_SNAPSHOT)
        return std::shared_ptr<Event>(new CommandEvent);
    else if (type == EVENT_ENTER_LOBBY)
        return std::shared_ptr<Event>(new CommandEvent);
    else if (type == EVENT_PLAY_AS_USER)
        return std::shared_ptr<Event>(new CommandEvent);
    else if (type == EVENT_PLAY_AS_BOT)
        return std::shared_ptr<Event>(new CommandEvent);
    else if (type == EVENT_ENTER_ROOM)
        return std::shared_ptr<Event>(new CommandEvent);*/
}