#ifndef CREATE_ROOM_EVENT_H
#define CREATE_ROOM_EVENT_H

#include "../Protocol.h"
#include "Event.h"

class CreateRoomEvent : public Event {
public:
	CreateRoomEvent();
    virtual void send(Protocol &protocol) override;
    virtual ~CreateRoomEvent() = default;
};

#endif // CREATE_ROOM_EVENT_H
