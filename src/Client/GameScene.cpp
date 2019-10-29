#include "GameScene.h"
#include "../Common/json.hpp"
#include "../Common/Constants.h"
#include "View/HealthBarFrontView.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

//TODO: class GameObjects

GameScene::GameScene(SdlWindow& window, Queue<ServerSnapshot*>& recvQueue, 
					BlockingQueue& sendQueue) : 
	window(window),
	isDone(false),
	recvQueue(recvQueue),
	sendQueue(sendQueue),	

	backgroundTex("background.png", window),
	background(backgroundTex),
	healthBarBackTex("health_background.png", window),
	healthBackground(healthBarBackTex),
	healthBarFrontTex("health_bar.png", window),
	healthBar(healthBarFrontTex),

	handler(window, audio, sendQueue),
	creator(window),
	conv(50), 
	cameraX(0), 
	cameraY(0),
	xScreen(0),
	yScreen(0) {
		window.fill();

		//Mock
		myID = 11;
		loadStage();
}

bool GameScene::done() {
	return isDone;
}

void GameScene::update() {
	audio.playMusic();
	window.getWindowSize(&xScreen, &yScreen);

	ServerSnapshot* snap;
	if (recvQueue.get(snap)) {
		updateCars(snap->getCars());
		updateGameEvents();
		delete snap;
	}
}

void GameScene::updateCars(CarList cars) {
	for (auto& car : cars) {
		ObjectViewPtr carView = gameObjects.at(car.id);
		carView->setRotation(car.angle);
		carView->move(conv.blockToPixel(car.x),
					  conv.blockToPixel(car.y));
		if (car.id == myID) {
			cameraX = xScreen/2 - conv.blockToPixel(car.x);
			cameraY = yScreen/2 - conv.blockToPixel(car.y);
			healthBar.resize(car.health);
		}
	}	
}

void GameScene::updateGameEvents() {

}

void GameScene::draw() {
	window.fill();
	drawBackground();
	for (auto& it : gameObjects) {
		it.second->drawAt(cameraX, cameraY);
	}
	drawDisplayObjects();
	window.render();
}

int GameScene::handle() {
	handler.handle();
	if (handler.done()) {
		isDone = true;
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
		gameObjects.insert(std::make_pair(ov->getId(), ov));
		if (ov->getId() == myID) {
			//Center camera in car
			window.getWindowSize(&xScreen, &yScreen);
			cameraX = xScreen/2 - x;
			cameraY = yScreen/2 - y;
		}
	}
}

void GameScene::drawBackground() { 
	background.setDims(xScreen, yScreen);
	for(int i = 0; i < 5; ++i) {
		for(int j = 0; j < 3; ++j) {
			background.drawAt(
				-xScreen*2 + xScreen*i + cameraX,
				-yScreen/2 + yScreen*j + cameraY);
		}
	}
}

void GameScene::drawDisplayObjects() {
	//HealthBar
	healthBackground.drawAt(xScreen*(0.8), yScreen*(0.9));
	healthBar.drawAt(xScreen*(0.8), yScreen*(0.9));
}