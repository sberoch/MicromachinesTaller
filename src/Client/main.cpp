#include "SdlWindow.h"
#include "SdlTexture.h"
#include "BackgroundView.h"
#include "InputHandler.h"
#include <SDL2/SDL.h>
#include "TextureCreator.h"
#include "../Common/Constants.h"
#include "../Common/Converter.h"
#include "../Common/json.hpp"

using json = nlohmann::json;

#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <map>

Converter conv(50); //number depends on zoom
SdlWindow window(1000,800);
SdlTexture bkgTex("background.png", window);
BackgroundView bkg(bkgTex);
InputHandler handler(window);
std::map<int, ObjectViewPtr> gameObjects;
TextureCreator creator(window);

static void draw();
static void loadStage();

int main(int argc, char const *argv[]) {

	loadStage();
	while(!handler.done()) {
	    draw();
	    handler.handle();
	    std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	return 0;
}

static void draw() {
	window.fill();

	//Background
	int xScreen, yScreen; 
	window.getWindowSize(&xScreen, &yScreen); //Fullscreen
	bkg.setDims(xScreen, yScreen);
	for(int i = 0; i < 5; ++i) {
		for(int j = 0; j < 3; ++j) {
			bkg.drawAt(-xScreen*2 + xScreen*i,
						-yScreen/2 + yScreen*j);
		}
	}

	//Views
	for (auto& it : gameObjects) {
		it.second->drawAt(0, 0);
	}

	window.render();
}

static void loadStage() {
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
