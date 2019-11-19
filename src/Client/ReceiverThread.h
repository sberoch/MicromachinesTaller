#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H

#include "../Common/Thread.h"
#include "../Common/Event/SnapshotEvent.h"
#include "../Common/Event/LobbySnapshot.h"
#include "../Common/Event/EndSnapshot.h"
#include "../Common/Queue.h"

class ReceiverThread : public Thread {
private:
	Queue<SnapshotEvent*>& gameRecvQueue;
	Queue<LobbySnapshot*>& lobbyRecvQueue;
	Queue<EndSnapshot*>& endRecvQueue;
	Protocol& protocol;
	bool _done;
	bool _isGameMode;
	int& _currentScene;
public:
	ReceiverThread(Queue<SnapshotEvent*>& gameRecvQueue,
				   Queue<LobbySnapshot*>& lobbyRecvQueue,
				   Queue<EndSnapshot*>& endRecvQueue,
				   Protocol& protocol, int& currentScene);

	virtual void run() override;
	void setGameMode();
	bool finished() const;

	ReceiverThread(ReceiverThread &copy) = delete;
	ReceiverThread& operator=(const ReceiverThread &c) = delete;
};

#endif // RECEIVER_THREAD_H
