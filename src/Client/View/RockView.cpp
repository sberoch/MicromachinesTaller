#include "RockView.h"

RockView::RockView(const SdlTexture& tex) : ObjectView(tex) {
	Area srcArea(0, 0, 720, 720);
	clips.push_back(srcArea);
	horizontalScale = HOR_PS_ROCK;
	verticalScale = VER_PS_ROCK;
}

void RockView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(initialX + x - horizontalScale/2,
				  initialY + y - verticalScale/2,
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea);
}