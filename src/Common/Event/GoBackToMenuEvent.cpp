//
// Created by alvaro on 23/11/19.
//

#include "GoBackToMenuEvent.h"

GoBackToMenuEvent::GoBackToMenuEvent(int clientId) {
    j["type"] = MENU;
    j["client_id"] = clientId;
}

void GoBackToMenuEvent::send(Protocol &protocol) {
    std::string toSend = j.dump();
    protocol.send(toSend);
}

GoBackToMenuEvent::~GoBackToMenuEvent() = default;
