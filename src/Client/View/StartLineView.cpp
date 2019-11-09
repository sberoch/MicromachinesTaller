#include "StartLineView.h"

StartLineView::StartLineView(const SdlTexture& tex, const int& angle) :
	ObjectView(tex), angle(angle) {
	Area srcArea(0, 0, 1430, 443);
	clips.push_back(srcArea);
	horizontalScale = HOR_PS_CURVE_TRACK;
	verticalScale = VER_PS_CURVE_TRACK/3;
}

void StartLineView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(initialX + x - horizontalScale/2,
				  initialY + y - verticalScale/2,
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea, (double) angle, SDL_FLIP_NONE);
}

int StartLineView::getAngle() {
	return angle;
}