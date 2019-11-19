//
// Created by alvaro on 19/11/19.
//

#ifndef MICROMACHINES_ENDSNAPSHOT_H
#define MICROMACHINES_ENDSNAPSHOT_H


#include "Event.h"

class EndSnapshot : public Event{
public:
    EndSnapshot();
    EndSnapshot(EndSnapshot& other);
    void send(Protocol& protocol) override;
    ~EndSnapshot() override;

    void addPlayerFinished(int idFromRoom);
};


#endif //MICROMACHINES_ENDSNAPSHOT_H
