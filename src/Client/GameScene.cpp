#include "GameScene.h"
#include "../Common/json.hpp"
#include "../Common/Constants.h"

#include <SDL2/SDL.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

GameScene::GameScene(SdlWindow& window, Queue<ServerSnapshot*>& recvQueue) : 
	window(window),
	isDone(false),
	backgroundTex("background.png", window),
	background(backgroundTex),
	handler(window),
	creator(window),
	conv(50),
	recvQueue(recvQueue) {
		window.fill();
		loadStage();
}

bool GameScene::done() {
	return isDone;
}

void GameScene::update() {
	ServerSnapshot* snap;
	if (recvQueue.get(snap)) {
		updateCars(snap->getCars());
		updateGameEvents();
		delete snap;
	}
}

void GameScene::updateCars(CarList cars) {
	for (auto& car : cars) {
		ObjectViewPtr carView = gameObjects.at(car["id"]);
		carView->setRotation(car["angle"]);
		carView->move(car["x"], car["y"]);
	}	
}

void GameScene::updateGameEvents() {

}

void GameScene::draw() {
	window.fill();
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	drawBackground();
	for (auto& it : gameObjects) {
		//TODO: change this to support camera.
		it.second->drawAt(0, 0);
	}
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
	int id, x, y, angle;
	std::ifstream i("scene.json");
	json j; i >> j;

	json objects = j["objects"];
	for (auto& obj : objects) {
		id = obj["type"].get<int>();
		x = conv.blockToPixel(obj["x"].get<int>());
		y = conv.blockToPixel(obj["y"].get<int>());
		angle = obj["angle"].get<int>();
		ObjectViewPtr ov = creator.create(id, x, y, angle);
		gameObjects.insert(std::make_pair(ov->getId(), ov));
	}
}

void GameScene::drawBackground() {
	int xScreen, yScreen; 
	window.getWindowSize(&xScreen, &yScreen); //Fullscreen
	background.setDims(xScreen, yScreen);
	for(int i = 0; i < 5; ++i) {
		for(int j = 0; j < 3; ++j) {
			background.drawAt(-xScreen*2 + xScreen*i,
						-yScreen/2 + yScreen*j);
		}
	}
}