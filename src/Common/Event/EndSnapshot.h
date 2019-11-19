//
// Created by alvaro on 19/11/19.
//

#ifndef MICROMACHINES_ENDSNAPSHOT_H
#define MICROMACHINES_ENDSNAPSHOT_H

#include "../Protocol.h"
#include "Event.h"
#include <string>

class EndSnapshot : public Event {
private:
	std::vector<int> finishedQueue;
public:
    EndSnapshot() = default;
    EndSnapshot(EndSnapshot& other);
    EndSnapshot(Protocol& protocol);
    void send(Protocol& protocol) override;
    const std::vector<int>& getFinishedQueue();
    ~EndSnapshot() override = default;

    void addPlayerFinished(int idFromRoom);
};


#endif //MICROMACHINES_ENDSNAPSHOT_H
