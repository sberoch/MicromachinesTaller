#include "MudSplatView.h"

MudSplatView::MudSplatView(const SdlTexture& tex) : ObjectView(tex) {
	Area srcArea(0, 0, 1100, 620);
	clips.push_back(srcArea);
	horizontalScale = 0;
	verticalScale = 0;
}

void MudSplatView::setDims(int x, int y) {
	horizontalScale = x;
	verticalScale = y;
}

void MudSplatView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(x - horizontalScale/2,
				  y - verticalScale/2,
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea);
}