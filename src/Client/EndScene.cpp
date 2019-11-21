#include "EndScene.h"
#include "../Common/Constants.h"
#include <iostream>

EndScene::EndScene(SdlWindow& window, SafeQueue<std::shared_ptr<EndSnapshot>>& endRecvQueue) :
	window(window),
	endRecvQueue(endRecvQueue),
	backgroundEndTex("end_screen.png", window),
	backgroundEnd(backgroundEndTex),
	creator(window),
	_done(false),
	fullscreen(true) {
		carViews.insert({TYPE_CAR_RED, creator.create(TYPE_CAR_RED, 0, 0, 270)});
    	carViews.insert({TYPE_CAR_BLUE, creator.create(TYPE_CAR_BLUE, 0, 0, 270)});
   		carViews.insert({TYPE_CAR_YELLOW, creator.create(TYPE_CAR_YELLOW, 0, 0, 270)});
    	carViews.insert({TYPE_CAR_GREEN, creator.create(TYPE_CAR_GREEN, 0, 0, 270)});
}

bool EndScene::done() {
	return _done;
}

void EndScene::update() {
	window.getWindowSize(&xScreen, &yScreen);
	backgroundEnd.setDims(xScreen, yScreen);

	arrivedPlayers.clear();
	std::shared_ptr<EndSnapshot> snap;
	if (endRecvQueue.get(snap)) {
	    for (auto& arrivedPlayer : snap->getFinishedQueue()) {
	    	arrivedPlayers.push_back(arrivedPlayer);
	    }
	}
}

void EndScene::draw() {
	window.fill();
	backgroundEnd.drawAt(xScreen/2, yScreen/2);
	drawCars();
	window.render();
}

Scene EndScene::handle() {
	while (SDL_PollEvent(&e) && !_done) {
		if (e.type == SDL_QUIT) {
			_done = true;

		} else if (e.type == SDL_MOUSEBUTTONDOWN) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (insideQuitButton(x, y)) {
				_done = true;
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
	return SCENE_END;
}

void EndScene::drawCars() {
	//TODO: dibujar solo los que haya en partida y en orden de llegada
	for (int i = 0; i < arrivedPlayers.size(); i++)	{
		carViews.at(static_cast<const ObjectType>(arrivedPlayers.at(i)))->
		drawAt(0.5 * xScreen, (0.27 + 0.14 * i) * yScreen);
	}
}

bool EndScene::insideQuitButton(int x, int y) {
	Area playBtn(0.75*xScreen, 0.75*yScreen, 0.25*xScreen, 0.2*yScreen);
	return playBtn.isInside(x, y);
}