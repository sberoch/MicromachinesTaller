#include "ReceiverThread.h"
#include <iostream>

ReceiverThread::ReceiverThread(Queue<SnapshotEvent*>& recvQueue, Protocol& protocol) :
	recvQueue(recvQueue),
	protocol(protocol),
	_done(false) {}

void ReceiverThread::run() {
	SnapshotEvent* snap;
	while(!_done) {
		snap = new SnapshotEvent(protocol);
		recvQueue.push(snap);
	} //TODO: ver condicion
}

void ReceiverThread::kill() {
	_done = true;
}

ReceiverThread::~ReceiverThread() {
	std::cout << "Recv thread killed.\n";
}