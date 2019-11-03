#include "ReceiverThread.h"
#include <iostream>

ReceiverThread::ReceiverThread(Queue<ServerSnapshot*>& recvQueue, Protocol& protocol) :
	recvQueue(recvQueue),
	protocol(protocol) {}

void ReceiverThread::run() {
	ServerSnapshot* snap;
	while(true) {
		snap = new ServerSnapshot(protocol);
		recvQueue.push(snap);
	} //TODO: ver condicion
}