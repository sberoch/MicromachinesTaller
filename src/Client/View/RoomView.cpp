#include "RoomView.h"

RoomView::RoomView(const SdlTexture& tex) : ObjectView(tex) {
	Area srcArea(0, 0, 600, 300);
	clips.push_back(srcArea);
	horizontalScale = 300;
	verticalScale = 150;
}

void RoomView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(x - horizontalScale/2,
				  y - verticalScale/2,
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea);
}