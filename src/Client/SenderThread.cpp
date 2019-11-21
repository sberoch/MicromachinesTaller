#include "SenderThread.h"
#include <iostream>

SenderThread::SenderThread(SafeQueue<std::shared_ptr<Event>>& sendQueue, Protocol& protocol) :
	sendQueue(sendQueue),
	protocol(protocol),
	_done(false) {}

void SenderThread::run() {
	try{
		std::shared_ptr<Event> event;
		while(true) {
			sendQueue.pop(event);
			if (event == nullptr) {
				break;
			}
			event->send(protocol);
		}
    } catch (std::exception &e) {
        std::cerr << "Error from sender Thread" << e.what() << std::endl;
    } catch (...){
        std::cerr << "Unknown error from sender Thread" << std::endl;
    }
	_done = true;
}

bool SenderThread::finished() const {
	return _done;
}