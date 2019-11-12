#include "SenderThread.h"
#include <iostream>

SenderThread::SenderThread(SafeQueue<Event*>& sendQueue, Protocol& protocol) : 
	sendQueue(sendQueue),
	protocol(protocol) {}

void SenderThread::run() {
	try{
	Event* event;
	while(true) {
		sendQueue.pop(event);
		if (event == nullptr){
			break;
		}
		std::cout << "sending from cli\n";
		event->send(protocol);
		delete event;
	}
} catch (std::exception &e) {
	std::cerr << e.what() << std::endl;
}
is_running = false;
}

bool SenderThread::finished() const {
	return !is_running;
}