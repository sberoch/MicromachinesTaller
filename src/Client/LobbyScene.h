#ifndef LOBBY_SCENE_H
#define LOBBY_SCENE_H

#include "BaseScene.h"
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "../Common/SafeQueue.h"
#include "../Common/Queue.h"
#include "../Common/Event/Event.h"
#include "../Common/Event/LobbySnapshot.h"
#include "TextureCreator.h"
#include "Audio.h"
#include "View/BackgroundView.h"
#include <vector>


class LobbyScene : public BaseScene {
private:
	SdlWindow& window;
	SafeQueue<Event*>& sendQueue;
	Queue<LobbySnapshot*>& lobbyRecvQueue;
	SdlTexture backgroundLobbyTex;
	BackgroundView backgroundLobby;
	Audio audio;
	TextureCreator creator;
	SDL_Event e;

	RoomsMap roomsMap;
	std::vector<ObjectViewPtr> roomViews;
	std::vector<ObjectViewPtr> playerViews;
	ObjectViewPtr arrow;
	ObjectViewPtr carSelected;

	bool _done;
	bool fullscreen;
	int selectedRoom;
	int selectedPlayer;
	int nextScene;
	int xScreen, yScreen;

	int& myId;
	bool hasJoinedARoom;
	bool& isBot;
public:
	LobbyScene(SdlWindow& window, Queue<LobbySnapshot*>& lobbyRecvQueue, 
				SafeQueue<Event*>& sendQueue, int& myId, bool& isBot);
	virtual bool done() override;
	virtual void update() override;
	virtual void draw() override;
	virtual int handle() override;
private:
	void updateRooms(RoomsMap roomsMap);
	void drawRooms();
	void drawPlayers();
	void drawArrows();
	bool insidePlayButton(int x, int y);
	bool insideUserButton(int x, int y);
	bool insideBotButton(int x, int y);
	bool insideCreateRoomButton(int x, int y);
	bool insideJoinRoomButton(int x, int y);
	void checkInsideAnyRoom(int x, int y);
	void checkInsideAnyPlayer(int x, int y);
};

#endif // LOBBY_SCENE_H
