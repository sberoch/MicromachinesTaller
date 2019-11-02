//
// Created by alvaro on 1/11/19.
//

#include "PlayAsUserEvent.h"

void PlayAsUserEvent::send(Protocol &protocol, int id) {
    j["type"] = PLAY_AS_USER;
    j["id"] = id;
    //AGREGAR ATRIBUTOS
    std::string toSend = j.dump();
    protocol.send(toSend);
}

PlayAsUserEvent::~PlayAsUserEvent() = default;
