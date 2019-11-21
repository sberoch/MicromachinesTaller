#include "LapsTextView.h"

LapsTextView::LapsTextView(const SdlTexture &tex) : ObjectView(tex) {
	Area srcArea(0, 0, 700, 400);
	clips.push_back(srcArea);
	horizontalScale = 150;
	verticalScale = 86;
}

void LapsTextView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(x - horizontalScale/2,
				  y - verticalScale/2,
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea);
}


