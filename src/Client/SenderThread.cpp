#include "SenderThread.h"
#include <iostream>

SenderThread::SenderThread(SafeQueue<Event*>& sendQueue, Protocol& protocol) : 
	sendQueue(sendQueue),
	protocol(protocol) {}

void SenderThread::run() {
	Event* event;
	while(true) {
		sendQueue.pop(event);
		event->send(protocol);
		delete event;
	}
}