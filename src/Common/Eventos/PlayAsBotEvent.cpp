//
// Created by alvaro on 1/11/19.
//

#include "PlayAsBotEvent.h"

void PlayAsBotEvent::send(Protocol &protocol, int id) {
    j["type"] = PLAY_AS_BOT;
    j["id"] = id;
    //AGREGAR ATRIBUTOS
    std::string toSend = j.dump();
    protocol.send(toSend);
}

PlayAsBotEvent::~PlayAsBotEvent() = default;
