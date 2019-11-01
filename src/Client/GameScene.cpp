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

GameScene::GameScene(SdlWindow& window, Queue<ServerSnapshot*>& recvQueue, 
					BlockingQueue& sendQueue) : 
	window(window),
	isDone(false),
	recvQueue(recvQueue),
	sendQueue(sendQueue),	

	backgroundTex("background.png", window),
	background(backgroundTex),
	
	handler(window, audio, sendQueue),
	creator(window),

	gameObjects(creator),
	bot(gameObjects),

	conv(PIXELS_PER_BLOCK), 
	cameraX(0), 
	cameraY(0),
	xScreen(0),
	yScreen(0),

	//Mock
	splatTestTex("mud_splat.png", window),
	splatTest(splatTestTex) {
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

	ServerSnapshot* snap;
	if (recvQueue.get(snap)) {
		updateCars(snap->getCars());
		updateGameEvents();
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
	gameObjects.draw(cameraX, cameraY);
	drawDisplayObjects();
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
		gameObjects.add(std::make_pair(ov->getId(), ov));
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
	//Mock (mudSplat)
	//splatTest.setDims(xScreen, yScreen);
	//splatTest.drawAt(xScreen/2, yScreen/2);
}