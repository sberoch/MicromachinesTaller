#include "SenderThread.h"

SenderThread::SenderThread(Queue<std::string>& sendQueue/*, protocol*/) : 
	sendQueue(sendQueue)
	/*protocol(protocol)*/ {}

void SenderThread::run() {
	//TODO: cola bloqueante

	/*while(true) {
		std::string command;
		sendQueue.get(command);
		protocol.send(command);
	}*/
}