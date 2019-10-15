#include "VistaPistaRecta.h"

VistaPistaRecta::VistaPistaRecta(const SdlTexture& tex, const int& angulo) :
	angulo(angulo) {
	this->textura = tex;
	Area srcArea(0, 0, 512, 688);
	clips.push_back(srcArea);
	tamanioHorizontal = 300;
	tamanioVertical = 300;
}

void VistaPistaRecta::dibujarEn(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(xInicial + x - tamanioHorizontal/2,
				  yInicial + y - tamanioVertical/2, 
				  tamanioHorizontal, tamanioVertical);
	textura.render(srcArea, destArea, (double) angulo, SDL_FLIP_NONE);
}

