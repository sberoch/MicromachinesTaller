#include "LobbyScene.h"

LobbyScene::LobbyScene(SdlWindow& window) :
	window(window),
	backgroundLobbyTex("lobby.png", window),
	backgroundLobby(backgroundLobbyTex),
	_done(false),
	fullscreen(true) {}

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
			if (insidePlayUserButton(x, y)) {
				audio.playEffect(SFX_BUTTON);
				nextScene = SCENE_GAME;
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

bool LobbyScene::insidePlayUserButton(int x, int y) {
	Area playBtn(0.7*xScreen, 0.7*yScreen, 0.3*xScreen, 0.1*yScreen);
	return playBtn.isInside(x, y);
}
