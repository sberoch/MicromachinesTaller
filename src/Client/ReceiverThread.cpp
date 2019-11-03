#include "ReceiverThread.h"
#include <iostream>

ReceiverThread::ReceiverThread(Queue<SnapshotEvent*>& recvQueue, Protocol& protocol) :
	recvQueue(recvQueue),
	protocol(protocol) {}

void ReceiverThread::run() {
	SnapshotEvent* snap;
	while(true) {
		snap = new SnapshotEvent(protocol);
		recvQueue.push(snap);
	} //TODO: ver condicion
}