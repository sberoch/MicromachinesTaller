#include "SenderThread.h"
#include <iostream>

SenderThread::SenderThread(SafeQueue<Event*>& sendQueue, Protocol& protocol) : 
	sendQueue(sendQueue),
	protocol(protocol) {}

void SenderThread::run() {
	Event* event;
	while(true) {
		sendQueue.pop(event);
		std::cout << "sending from cli\n";
		event->send(protocol);
		delete event;
	}
}