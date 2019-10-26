#include "CarView.h"

CarView::CarView(const SdlTexture& tex, const int& angle) :
	angle(angle), posX(0), posY(0) {
	this->texture = tex;
	Area srcArea(0, 0, 463, 1010);
	clips.push_back(srcArea);
	horizontalScale = 50;
	verticalScale = 100;
}

void CarView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(initialX + x + posX - horizontalScale/2,
				  initialY + y + posY - verticalScale/2, 
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea, (double) angle, SDL_FLIP_NONE);
}

void CarView::move(int x, int y) {
	posX = x;
	posY = y;
}

void CarView::setRotation(int angle) {
	this->angle = angle;
}