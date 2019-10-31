#include "SenderThread.h"

SenderThread::SenderThread(SafeQueue& sendQueue, Protocol& protocol) :
	sendQueue(sendQueue),
	protocol(protocol) {}

void SenderThread::run() {
	std::string command;
	while(true) {
		sendQueue.pop(command);
		protocol.send(command);
	}
}