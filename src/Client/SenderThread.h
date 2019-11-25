#ifndef SENDER_THREAD_H
#define SENDER_THREAD_H

#include "../Common/Thread.h"
#include "../Common/SafeQueue.h"
#include "../Common/Protocol.h"
#include "../Common/Event/Event.h"

class SenderThread : public Thread {
private:
	SafeQueue<std::shared_ptr<Event>>& sendQueue;
	Protocol& protocol;
	bool _done;
public:
	SenderThread(SafeQueue<std::shared_ptr<Event>>& sendQueue, Protocol& protocol);

	bool finished() const;
	void run() override;
};

#endif // SENDER_THREAD_H
