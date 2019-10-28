#ifndef SENDER_THREAD_H
#define SENDER_THREAD_H

#include "../Common/Thread.h"
#include "../Common/Queue.h"
#include "../Common/BlockingQueue.h"
#include "../Common/Protocol.h"
#include <string>

class SenderThread : public Thread {
private:
	BlockingQueue& sendQueue;
	Protocol& protocol;
public:
	SenderThread(BlockingQueue& sendQueue, Protocol& protocol);
	virtual void run() override;
};

#endif // SENDER_THREAD_H
