#include "CurveTrackView.h"

CurveTrackView::CurveTrackView(const SdlTexture& tex, const int& angle) :
	angle(angle) {
	this->texture = tex;
	Area srcArea(0, 0, 691, 691);
	clips.push_back(srcArea);
	horizontalScale = 300;
	verticalScale = 300;
}

void CurveTrackView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(initialX + x - horizontalScale/2,
				  initialY + y - verticalScale/2, 
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea, (double) angle, SDL_FLIP_NONE);
}

