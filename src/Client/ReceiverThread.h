#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H

#include "../Common/Thread.h"
#include "../Common/ServerSnapshot.h"
#include "../Common/Queue.h"
#include "../Server/EventProtocol.cpp"

class ReceiverThread : public Thread {
private:
	Queue<ServerSnapshot*>& recvQueue;
	//EventProtocol protocol;
public:
	ReceiverThread(Queue<ServerSnapshot*>& recvQueue,
			const std::string& host, const std::string& port);
	virtual void run() override;
};

#endif // RECEIVER_THREAD_H
