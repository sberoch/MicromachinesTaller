#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H

#include "../Common/Thread.h"
#include "../Common/Event/SnapshotEvent.h"
#include "../Common/Event/LobbySnapshot.h"
#include "../Common/Queue.h"

class ReceiverThread : public Thread {
private:
	Queue<SnapshotEvent*>& gameRecvQueue;
	Queue<LobbySnapshot*>& lobbyRecvQueue;
	Protocol& protocol;
	bool _done;
	bool _isLobbyMode;
public:
	ReceiverThread(Queue<SnapshotEvent*>& gameRecvQueue,
				   Queue<LobbySnapshot*>& lobbyRecvQueue, 
				   Protocol& protocol);
	void kill();
	virtual void run() override;
	void setGameMode();
	~ReceiverThread();
};

#endif // RECEIVER_THREAD_H
