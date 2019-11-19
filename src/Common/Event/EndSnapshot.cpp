//
// Created by alvaro on 19/11/19.
//

#include <iostream>
#include "EndSnapshot.h"

EndSnapshot::EndSnapshot() {}

EndSnapshot::EndSnapshot(EndSnapshot &other) {
    this->j = other.j;
}

void EndSnapshot::addPlayerFinished(int idFromRoom){
    j["finished_queue"].push_back(idFromRoom);
}

void EndSnapshot::send(Protocol &protocol) {
    std::string finishedQueue = j.dump();
    std::cout << "Dumped:" << finishedQueue << std::endl;
    protocol.send(finishedQueue);
}



EndSnapshot::~EndSnapshot() {

}
