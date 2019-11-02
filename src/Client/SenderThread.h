#ifndef SENDER_THREAD_H
#define SENDER_THREAD_H

#include "../Common/Thread.h"
#include "../Common/SafeQueue.h"
#include "../Common/Protocol.h"
#include "../Common/Event/Event.h"

class SenderThread : public Thread {
private:
	SafeQueue<Event*>& sendQueue;
	Protocol& protocol;
public:
	SenderThread(SafeQueue<Event*>& sendQueue, Protocol& protocol);
	virtual void run() override;
};

#endif // SENDER_THREAD_H
