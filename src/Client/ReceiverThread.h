#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H

#include "../Common/Thread.h"
#include "../Common/ServerSnapshot.h"
#include "../Common/Queue.h"

class ReceiverThread : public Thread {
private:
	Queue<ServerSnapshot*>& recvQueue;
	Protocol& protocol;
public:
	ReceiverThread(Queue<ServerSnapshot*>& recvQueue, Protocol& protocol);
	virtual void run() override;
};

#endif // RECEIVER_THREAD_H
