#include "ReceiverThread.h"
#include <iostream>

ReceiverThread::ReceiverThread(Queue<ServerSnapshot*>& recvQueue) :
	recvQueue(recvQueue) {}

void ReceiverThread::run() {
	//TODO: loop that recvs from server

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