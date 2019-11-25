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
	SafeQueue<std::shared_ptr<SnapshotEvent>>& gameRecvQueue;
	SafeQueue<std::shared_ptr<LobbySnapshot>>& lobbyRecvQueue;
	SafeQueue<std::shared_ptr<EndSnapshot>>& endRecvQueue;
	Protocol& protocol;
	bool _done;
	bool _isGameMode;
	Scene& _currentScene;

public:
	ReceiverThread(SafeQueue<std::shared_ptr<SnapshotEvent>>& gameRecvQueue,
					SafeQueue<std::shared_ptr<LobbySnapshot>>& lobbyRecvQueue,
					SafeQueue<std::shared_ptr<EndSnapshot>>& endRecvQueue,
					Protocol& protocol, Scene& currentScene);

	void run() override;
	bool finished() const;

	ReceiverThread(ReceiverThread &copy) = delete;
	ReceiverThread& operator=(const ReceiverThread &c) = delete;

private:
	void receiveLobbySnapshots();
	void receiveGameSnapshots();
	void receiveEndSnapshots();
};

#endif // RECEIVER_THREAD_H
