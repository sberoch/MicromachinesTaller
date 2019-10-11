
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "VistaFondo.h"
#include "InputHandler.h"
#include <SDL2/SDL.h>

#include <thread>
#include <chrono>
#include <iostream>

SdlWindow window(1000,800);
SdlTexture fondoTex("fondo.png", window);
VistaFondo fondo(fondoTex);
InputHandler handler(window);

static void dibujar();

int main(int argc, char const *argv[]) {

	while(!handler.termino()) {
	    dibujar();
	    handler.handle();
	    std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	return 0;
}

static void dibujar() {
	window.fill();

	int xScreen, yScreen; 
	window.getWindowSize(&xScreen, &yScreen); //Fullscreen siempre
	fondo.setDimensiones(xScreen, yScreen);
	for(int i = 0; i < 5; ++i) {
		for(int j = 0; j < 3; ++j) {
			fondo.dibujarEn(-xScreen*2 + xScreen*i,
						-yScreen/2 + yScreen*j);
		}
	}

	window.render();
}
