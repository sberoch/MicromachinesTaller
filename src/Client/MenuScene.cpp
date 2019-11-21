#include "MenuScene.h"
#include "../Common/Constants.h"
#include "../Common/Event/EnterLobbyEvent.h"
#include <iostream>

MenuScene::MenuScene(SdlWindow& window, SafeQueue<std::shared_ptr<Event>>& sendQueue) :
	window(window),
	sendQueue(sendQueue),
	backgroundMenuTex("menu_background.png", window),
	backgroundMenu(backgroundMenuTex),
	_done(false),
	fullscreen(true) {}

bool MenuScene::done() {
	return _done;
}

void MenuScene::update() {
	window.getWindowSize(&xScreen, &yScreen);
	backgroundMenu.setDims(xScreen, yScreen);
}

void MenuScene::draw() {
	window.fill();
	backgroundMenu.drawAt(xScreen/2, yScreen/2);
	window.render();
}

Scene MenuScene::handle() {
	nextScene = SCENE_MENU;
	while (SDL_PollEvent(&e) && !_done) {
		if (e.type == SDL_QUIT) {
			_done = true;

		} else if (e.type == SDL_MOUSEBUTTONDOWN) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (insideQuitButton(x, y)) {
				audio.playEffect(SFX_BUTTON);	
				_done = true;
				
			} else if (insidePlayButton(x, y)) {
				audio.playEffect(SFX_BUTTON);
				std::shared_ptr<Event> play(new EnterLobbyEvent());
				sendQueue.push(play);
				nextScene = SCENE_LOBBY;
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

bool MenuScene::insidePlayButton(int x, int y) {
	Area playBtn(0.4*xScreen, 0.6*yScreen, 0.3*xScreen, 0.15*yScreen);
	return playBtn.isInside(x, y);
}

bool MenuScene::insideQuitButton(int x, int y) {
	Area quitBtn(0.45*xScreen, 0.8*yScreen, 0.2*xScreen, 0.15*yScreen);
	return quitBtn.isInside(x, y);
}
