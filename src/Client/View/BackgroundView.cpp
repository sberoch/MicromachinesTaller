#include "BackgroundView.h"

BackgroundView::BackgroundView(const SdlTexture& tex) {
	this->texture = tex;
	Area srcArea(0, 0, 2048, 1152);
	clips.push_back(srcArea);
	horizontalScale = 0;
	verticalScale = 0;
}

void BackgroundView::setDims(int x, int y) {
	horizontalScale = x;
	verticalScale = y;
}

void BackgroundView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(x - horizontalScale/2, y - verticalScale/2, horizontalScale, verticalScale);
	texture.render(srcArea, destArea);
}

