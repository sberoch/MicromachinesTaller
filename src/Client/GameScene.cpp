#include "GameScene.h"
#include "../Common/json.hpp"
#include "../Common/Constants.h"
#include <iostream>

using json = nlohmann::json;

GameScene::GameScene(SdlWindow& window, Queue<SnapshotEvent*>& recvQueue, 
					SafeQueue<Event*>& sendQueue, int& myId, bool& isBot) : 
	window(window),
	isDone(false),
	recvQueue(recvQueue),
	sendQueue(sendQueue),
	myId(myId),

	backgroundTex("background.png", window),
	background(backgroundTex),
	display(window),
	
	handler(window, audio, sendQueue, myId),
	creator(window),

	gameObjects(creator),
	bot(gameObjects, audio, sendQueue),
	conv(PIXELS_PER_BLOCK), 
	xScreen(0),
	yScreen(0),
	nextScene(SCENE_GAME),
	isBot(isBot),
	isGameOver(false),
	isMapReady(false) {}

bool GameScene::done() {
	return isDone;
}

void GameScene::update() {
	audio.playMusic();
	window.getWindowSize(&xScreen, &yScreen);

	SnapshotEvent* snap;
	if (recvQueue.pop(snap)) {
		updateCars(snap->getCars());
		updateGameEvents(snap->getGameEvents());
		delete snap;
	}
}

void GameScene::updateCars(CarList cars) {
	for (auto& car : cars) {
		ObjectViewPtr carView = gameObjects.getCar(car.id);
		carView->setRotation(car.angle);
		carView->move(conv.blockToPixel(car.x),
					  conv.blockToPixel(car.y));
		if (car.id == myId) {
			display.update(xScreen/2 - conv.blockToPixel(car.x),
						   yScreen/2 - conv.blockToPixel(car.y),
						   car.health);
		}
	}	
}

void GameScene::updateGameEvents(GameEventsList gameEvents) {
	for (auto& gameEvent : gameEvents) {
 		switch(gameEvent.eventType) {
			case ADD: addObject(gameEvent); break;
			case REMOVE: removeObject(gameEvent); break;
			case ID_ASSIGN: isMapReady = true; bot.setPlayerId(gameEvent.id); break;
			case MUD_SPLAT: display.showMudSplat(); break;
			case GAME_OVER: nextScene = SCENE_END; break;
			default: break;
		}
	}
}

void GameScene::addObject(GameEventStruct gameEvent) {
	ObjectViewPtr ov = creator.create(gameEvent.objectType, 
										conv.blockToPixel(gameEvent.x), 
										conv.blockToPixel(gameEvent.y), 
										gameEvent.angle);
	gameObjects.add(gameEvent.objectType, gameEvent.id, ov);
}

void GameScene::removeObject(GameEventStruct gameEvent) {
	gameObjects.remove(gameEvent.objectType, gameEvent.id);
}

void GameScene::draw() {
	window.fill();
	drawBackground();
	gameObjects.draw(display.cam_x, display.cam_y);
	display.draw();
	window.render();
}

int GameScene::handle() {
	if (isMapReady) {
		if (isBot) {
			bot.handle();

		} else {
			handler.handle();
			if (handler.done()) {
				isDone = true;
			}
		}
	}
	return nextScene;
}

void GameScene::drawBackground() { 
	background.setDims(xScreen, yScreen);
	for(int i = 0; i < 5; ++i) {
		for(int j = 0; j < 3; ++j) {
			background.drawAt(
				-xScreen*2 + xScreen*i + display.cam_x,
				-yScreen/2 + yScreen*j + display.cam_y);
		}
	}
}