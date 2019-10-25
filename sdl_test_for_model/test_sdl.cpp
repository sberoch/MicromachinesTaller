#include <iostream>
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "CarView.h"
#include "InputHandler.h"
#include <thread>
#include <chrono>

int main(int argc, char const *argv[]) {
	SdlWindow window(1000, 800);
	SdlTexture carTex("car_1.png", window);
	CarView car(carTex, 0);
	car.setInitialPos(800, 400);
	InputHandler handler(window);

	while(!handler.done()) {
	    window.fill();
	    std::this_thread::sleep_for(std::chrono::milliseconds(20));
	    car.drawAt(0, 0);
	    window.render();
	    handler.handle();
	}

	return 0;
}
