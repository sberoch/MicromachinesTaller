#include "CarView.h"

CarView::CarView(const SdlTexture& tex, const int& angle) :
	ObjectView(tex), angle(angle) {
	Area srcArea(0, 0, 463, 1010);
	clips.push_back(srcArea);
	horizontalScale = HOR_PS_CAR;
	verticalScale = VER_PS_CAR;
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

int CarView::getAngle() {
	return angle;
}