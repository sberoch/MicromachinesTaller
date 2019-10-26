#ifndef SENDER_THREAD_H
#define SENDER_THREAD_H

#include "../Common/Thread.h"
#include "../Common/Queue.h"
#include <string>

class SenderThread : public Thread {
private:
	Queue<std::string>& sendQueue;
	//EventProtocol& protocol;
public:
	SenderThread(Queue<std::string>& sendQueue/*, protocol*/);
	virtual void run() override;
};

#endif // SENDER_THREAD_H
