#ifndef LOBBY_SCENE_H
#define LOBBY_SCENE_H

#include "BaseScene.h"
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "../Common/SafeQueue.h"
#include "../Common/Queue.h"
#include "../Common/Event/Event.h"
#include "../Common/Event/LobbySnapshot.h"
#include "Audio.h"
#include "View/BackgroundView.h"

class LobbyScene : public BaseScene {
private:
	SdlWindow& window;
	SafeQueue<Event*>& sendQueue;
	Queue<LobbySnapshot*>& lobbyRecvQueue;
	SdlTexture backgroundLobbyTex;
	BackgroundView backgroundLobby;
	Audio audio;
	SDL_Event e;

	bool _done;
	bool fullscreen;
	int nextScene;
	int xScreen, yScreen;
	int myId;
public:
	LobbyScene(SdlWindow& window, Queue<LobbySnapshot*>& lobbyRecvQueue, 
				SafeQueue<Event*>& sendQueue);
	virtual bool done() override;
	virtual void update() override;
	virtual void draw() override;
	virtual int handle() override;
private:
	bool insidePlayButton(int x, int y);
	bool insideUserButton(int x, int y);
	bool insideBotButton(int x, int y);
	bool insideCreateRoomButton(int x, int y);
	bool insideJoinRoomButton(int x, int y);
};

#endif // LOBBY_SCENE_H
