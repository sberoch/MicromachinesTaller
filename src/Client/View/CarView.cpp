#include "CarView.h"

CarView::CarView(const SdlTexture& tex, const int& angle) :
	angle(angle) {
	this->texture = tex;
	Area srcArea(0, 0, 463, 1010);
	clips.push_back(srcArea);
	horizontalScale = 50;
	verticalScale = 100;
}

void CarView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(initialX + x - horizontalScale/2,
				  initialY + y - verticalScale/2, 
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea, (double) angle, SDL_FLIP_NONE);
}

void CarView::move(int x, int y) {
	initialX = x;
	initialY = y;
}

void CarView::setRotation(int angle) {
	this->angle = angle;
}