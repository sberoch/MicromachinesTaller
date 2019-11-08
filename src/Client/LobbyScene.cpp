#include "LobbyScene.h"
#include "../Common/Event/EnterRoomEvent.h"
#include "../Common/Event/CreateRoomEvent.h"
#include "../Common/Event/PlayAsUserEvent.h"
#include "../Common/Event/PlayAsBotEvent.h"
#include "../Common/Event/PlayEvent.h"

LobbyScene::LobbyScene(SdlWindow& window, Queue<LobbySnapshot*>& lobbyRecvQueue,
						 SafeQueue<Event*>& sendQueue) :
	window(window),
	lobbyRecvQueue(lobbyRecvQueue),
	sendQueue(sendQueue),
	backgroundLobbyTex("lobby.png", window),
	backgroundLobby(backgroundLobbyTex),
	_done(false),
	fullscreen(true) {
		myId = 0;
	}

bool LobbyScene::done() {
	return _done;
}

void LobbyScene::update() {
	window.getWindowSize(&xScreen, &yScreen);
	backgroundLobby.setDims(xScreen, yScreen);
	//TODO: recibir de sv salas y jugadores
}

void LobbyScene::draw() {
	window.fill();
	backgroundLobby.drawAt(xScreen/2, yScreen/2);
	//TODO: jugadores y salas
	window.render();
}

int LobbyScene::handle() {
	nextScene = SCENE_LOBBY;
	while (SDL_PollEvent(&e) && !_done) {
		if (e.type == SDL_QUIT) {
			_done = true;

		} else if (e.type == SDL_MOUSEBUTTONDOWN) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (insidePlayButton(x, y)) {
				sendQueue.push(new PlayEvent(myId));
				audio.playEffect(SFX_BUTTON);
				nextScene = SCENE_GAME;
			}
			else if (insideUserButton(x, y)) {
				sendQueue.push(new PlayAsUserEvent(myId));
				audio.playEffect(SFX_BUTTON);
			}
			else if (insideBotButton(x, y)) {
				sendQueue.push(new PlayAsBotEvent(myId));
				audio.playEffect(SFX_BUTTON);
			}
			else if (insideCreateRoomButton(x, y)) {
				sendQueue.push(new CreateRoomEvent());
				audio.playEffect(SFX_BUTTON);
			}
			else if (insideJoinRoomButton(x, y)) {
				sendQueue.push(new EnterRoomEvent(myId));
				audio.playEffect(SFX_BUTTON);
			}

		} else if (e.type == SDL_KEYDOWN) {
			SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) e;
			if (keyEvent.keysym.sym == SDLK_F11) {
				if (fullscreen) {
					window.setFullscreen(false);
					fullscreen = false;
				} else {
					window.setFullscreen(true);
					fullscreen = true;
				}
			}
		}
	}
	
	return nextScene;
}

bool LobbyScene::insidePlayButton(int x, int y) {
	Area playBtn(0.4*xScreen, 0.8*yScreen, 0.2*xScreen, 0.15*yScreen);
	return playBtn.isInside(x, y);
}

bool LobbyScene::insideUserButton(int x, int y) {
	Area playBtn(0.7*xScreen, 0.75*yScreen, 0.3*xScreen, 0.1*yScreen);
	return playBtn.isInside(x, y);
}

bool LobbyScene::insideBotButton(int x, int y) {
	Area playBtn(0.7*xScreen, 0.87*yScreen, 0.3*xScreen, 0.1*yScreen);
	return playBtn.isInside(x, y);
}

bool LobbyScene::insideCreateRoomButton(int x, int y) {
	Area playBtn(0, 0.75*yScreen, 0.3*xScreen, 0.1*yScreen);
	return playBtn.isInside(x, y);
}

bool LobbyScene::insideJoinRoomButton(int x, int y) {
	Area playBtn(0, 0.87*yScreen, 0.3*xScreen, 0.1*yScreen);
	return playBtn.isInside(x, y);
}

