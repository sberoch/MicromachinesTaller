#include "OilView.h"

OilView::OilView(const SdlTexture& tex, const int& angle) :
	ObjectView(tex), angle(angle) {
	Area srcArea(0, 0, 871, 374);
	clips.push_back(srcArea);
	horizontalScale = HOR_PS_OIL;
	verticalScale = VER_PS_OIL;
}

void OilView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(initialX + x - horizontalScale/2,
				  initialY + y - verticalScale/2, 
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea, (double) angle, SDL_FLIP_NONE);
}