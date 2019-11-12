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
	bool _isGameMode;
public:
	ReceiverThread(Queue<SnapshotEvent*>& gameRecvQueue,
				   Queue<LobbySnapshot*>& lobbyRecvQueue, 
				   Protocol& protocol);
	virtual void run() override;
	void setGameMode();
	bool finished() const;
	bool is_running{true};
	ReceiverThread(ReceiverThread &copy) = delete;
	ReceiverThread& operator=(const ReceiverThread &c) = delete;
	~ReceiverThread();
};

#endif // RECEIVER_THREAD_H
