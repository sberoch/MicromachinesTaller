#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H

#include "../Common/Thread.h"
#include "../Common/Event/SnapshotEvent.h"
#include "../Common/Event/LobbySnapshot.h"
#include "../Common/Event/EndSnapshot.h"
#include "../Common/Constants.h"
#include "../Common/SafeQueue.h"

class ReceiverThread : public Thread {
private:
	SafeQueue<SnapshotEvent*>& gameRecvQueue;
	SafeQueue<LobbySnapshot*>& lobbyRecvQueue;
	SafeQueue<EndSnapshot*>& endRecvQueue;
	Protocol& protocol;
	bool _done;
	bool _isGameMode;
	Scene& _currentScene;
public:
	ReceiverThread(SafeQueue<SnapshotEvent*>& gameRecvQueue,
				   SafeQueue<LobbySnapshot*>& lobbyRecvQueue,
				   SafeQueue<EndSnapshot*>& endRecvQueue,
				   Protocol& protocol, Scene& currentScene);

	virtual void run() override;
	void setGameMode();
	bool finished() const;

	ReceiverThread(ReceiverThread &copy) = delete;
	ReceiverThread& operator=(const ReceiverThread &c) = delete;
};

#endif // RECEIVER_THREAD_H
