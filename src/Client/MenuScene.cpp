#include "MenuScene.h"
#include "../Common/Constants.h"
#include "../Common/Event/EnterLobbyEvent.h"
#include <iostream>

MenuScene::MenuScene(SdlWindow& window, SafeQueue<Event*>& sendQueue) : 
	window(window),
	sendQueue(sendQueue),
	backgroundMenuTex("menu_background.png", window),
	backgroundMenu(backgroundMenuTex),
	_done(false),
	fullscreen(true),
	nextScene(SCENE_MENU){}

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

int MenuScene::handle(SDL_Event& event) {
	std::cout << "asdasdad\n";
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (insideQuitButton(x, y)) {
			audio.playEffect(SFX_BUTTON);
			_done = true;

		} else if (insidePlayButton(x, y)) {
			audio.playEffect(SFX_BUTTON);
			sendQueue.push(new EnterLobbyEvent());
			nextScene = SCENE_LOBBY;
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
