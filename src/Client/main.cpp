
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "BackgroundView.h"
#include "InputHandler.h"
#include <SDL2/SDL.h>
#include "TextureCreator.h"
#include "../Common/Constants.h"

#include <thread>
#include <chrono>
#include <iostream>

SdlWindow window(1000,800);
SdlTexture bkgTex("background.png", window);
BackgroundView bkg(bkgTex);
InputHandler handler(window);

TextureCreator creator(window);
ObjectViewPtr straightTrack = creator.create(ID_STRAIGHT_TRACK, 700, 450, 90);
ObjectViewPtr curveTrack1 = creator.create(ID_CURVE_TRACK, 700, 150, 90);
ObjectViewPtr curveTrack2 = creator.create(ID_CURVE_TRACK, 700, 750, 270);

static void draw();

int main(int argc, char const *argv[]) {

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
	straightTrack->drawAt(0, 0);
	curveTrack1->drawAt(0, 0);
	curveTrack2->drawAt(0, 0);

	window.render();
}
