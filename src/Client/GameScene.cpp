#include "GameScene.h"
#include "../Common/json.hpp"
#include "../Common/Constants.h"
#include "View/HealthBarFrontView.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

//Mock
#include "View/MudSplatView.h"

using json = nlohmann::json;

GameScene::GameScene(SdlWindow& window, Queue<SnapshotEvent*>& recvQueue, 
					SafeQueue<Event*>& sendQueue) : 
	window(window),
	isDone(false),
	recvQueue(recvQueue),
	sendQueue(sendQueue),

	backgroundTex("background.png", window),
	background(backgroundTex),
	display(window),
	
	handler(window, audio, sendQueue),
	creator(window),

	gameObjects(creator),
	bot(gameObjects),

	conv(PIXELS_PER_BLOCK), 
	xScreen(0),
	yScreen(0) {
		window.fill();

		//Mock
		myID = 11;
		isBot = false;
		loadStage();
}

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
		ObjectViewPtr carView = gameObjects.get(car.id);
		carView->setRotation(car.angle);
		carView->move(conv.blockToPixel(car.x),
					  conv.blockToPixel(car.y));
		if (car.id == myID) {
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
			default: break;
		}
	}
}

void GameScene::addObject(GameEventStruct gameEvent) {
	ObjectViewPtr ov = creator.create(gameEvent.objectType, 
										conv.blockToPixel(gameEvent.x), 
										conv.blockToPixel(gameEvent.y), 
										gameEvent.angle);
	gameObjects.add(ov->getId(), ov);
}

void GameScene::removeObject(GameEventStruct gameEvent) {

}

void GameScene::draw() {
	window.fill();
	drawBackground();
	gameObjects.draw(display.cam_x, display.cam_y);
	display.draw();
	window.render();
}

int GameScene::handle() {
	if (isBot) {
		bot.handle();

	} else {
		handler.handle();
		if (handler.done()) {
			isDone = true;
		}
	}
	//TODO: change this to support a final scene.
	return SCENE_GAME;
}

void GameScene::loadStage() {
	//TODO: this is sent by server
	int type, x, y, angle;
	std::ifstream i("test_scene.json");
	json j; i >> j;

	json objects = j["objects"];
	for (auto& obj : objects) {
		type = obj["type"].get<int>();
		x = conv.blockToPixel(obj["x"].get<int>());
		y = conv.blockToPixel(obj["y"].get<int>());
		angle = obj["angle"].get<int>();
		ObjectViewPtr ov = creator.create(type, x, y, angle);
		gameObjects.add(ov->getId(), ov);
		if (ov->getId() == myID) {
			//Center camera in car
			window.getWindowSize(&xScreen, &yScreen);
			display.cam_x = xScreen/2 - x;
			display.cam_y = yScreen/2 - y;
		}
	}

	//Mock
	//display.showMudSplat();
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