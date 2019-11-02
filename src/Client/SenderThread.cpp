#include "SenderThread.h"

SenderThread::SenderThread(BlockingQueue& sendQueue, Protocol& protocol) : 
	sendQueue(sendQueue),
	protocol(protocol) {}

void SenderThread::run() {
	std::string command;
	while(true) {
		sendQueue.pop(command);
		protocol.send(command);
	} //TODO: ver condicion
}