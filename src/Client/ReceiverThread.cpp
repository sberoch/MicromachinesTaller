#include "ReceiverThread.h"
#include <iostream>

ReceiverThread::ReceiverThread(Queue<ServerSnapshot*>& recvQueue,
		const std::string& host, const std::string& port) :
	recvQueue(recvQueue),
	/*protocol(host, port)*/ {}

void ReceiverThread::run() {
	/*ServerSnapshot* snap;
	while(true) {
		snap = new ServerSnapshot(protocol);
		recvQueue.put(snap);
	}*/

	//Mock
	ServerSnapshot* snap;
	for(unsigned i = 0; i < 100; ++i) {
		snap = new ServerSnapshot();
		snap->setCar(15, 7 + (float)i/50, 180, 11);
		recvQueue.put(snap);
	}

	for(unsigned i = 0; i < 50; ++i) {
		snap = new ServerSnapshot();
		snap->setCar(15, 9, 180 + i, 11);
		recvQueue.put(snap);
	}
}