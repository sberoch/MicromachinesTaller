#ifndef PLAY_EVENT_H
#define PLAY_EVENT_H

#include "Event.h"

class PlayEvent : public Event {
public:
	PlayEvent(int id);
	virtual void send(Protocol &protocol) override;
    virtual ~PlayEvent() = default;
};

#endif // PLAY_EVENT_H
