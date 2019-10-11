#include "VistaFondo.h"

#include <iostream>

VistaFondo::VistaFondo(const SdlTexture& tex) {
	this->textura = tex;
	Area srcArea(0, 0, 1920, 1080);
	clips.push_back(srcArea);
	tamanioHorizontal = 0;
	tamanioVertical = 0;
}

void VistaFondo::setDimensiones(int x, int y) {
	tamanioHorizontal = x;
	tamanioVertical = y;
}

void VistaFondo::dibujarEn(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(x - tamanioHorizontal/2, y - tamanioVertical/2, tamanioHorizontal, tamanioVertical);
	textura.render(srcArea, destArea);
}

