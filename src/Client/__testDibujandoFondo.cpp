
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "VistaFondo.h"
#include "InputHandler.h"
#include <SDL2/SDL.h>
#include "CreadorTexturas.h"
#include "../Common/Constantes.h"

#include <thread>
#include <chrono>
#include <iostream>

SdlWindow window(1000,800);
SdlTexture fondoTex("fondo.png", window);
VistaFondo fondo(fondoTex);
InputHandler handler(window);

CreadorTexturas creadorTex(window);
VistaObjetoPtr pistaRecta = creadorTex.crear(ID_PISTA_RECTA, 800, 450, 90);
VistaObjetoPtr pistaCurva = creadorTex.crear(ID_PISTA_CURVA, 800, 150, 90);

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

	//Background
	int xScreen, yScreen; 
	window.getWindowSize(&xScreen, &yScreen); //Fullscreen siempre
	fondo.setDimensiones(xScreen, yScreen);
	for(int i = 0; i < 5; ++i) {
		for(int j = 0; j < 3; ++j) {
			fondo.dibujarEn(-xScreen*2 + xScreen*i,
						-yScreen/2 + yScreen*j);
		}
	}

	//Views
	pistaRecta->dibujarEn(0, 0);
	pistaCurva->dibujarEn(0, 0);

	window.render();
}
