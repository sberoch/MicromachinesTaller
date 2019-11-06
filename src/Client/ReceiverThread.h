#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H

#include "../Common/Thread.h"
#include "../Common/Event/SnapshotEvent.h"
#include "../Common/Queue.h"

class ReceiverThread : public Thread {
private:
	Queue<SnapshotEvent*>& recvQueue;
	Protocol& protocol;
	bool _done;
public:
	ReceiverThread(Queue<SnapshotEvent*>& recvQueue, Protocol& protocol);
	virtual void run() override;
	~ReceiverThread();
};

#endif // RECEIVER_THREAD_H
