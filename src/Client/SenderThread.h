#ifndef SENDER_THREAD_H
#define SENDER_THREAD_H

#include "../Common/Thread.h"
#include "../Common/Queue.h"
#include "../Common/SafeQueue.h"
#include "../Common/Protocol.h"
#include <string>

class SenderThread : public Thread {
private:
	SafeQueue& sendQueue;
	Protocol& protocol;
public:
	SenderThread(SafeQueue& sendQueue, Protocol& protocol);
	virtual void run() override;
};

#endif // SENDER_THREAD_H
