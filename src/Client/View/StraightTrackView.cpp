#include "StraightTrackView.h"

StraightTrackView::StraightTrackView(const SdlTexture& tex, const int& angle) :
	angle(angle) {
	this->texture = tex;
	Area srcArea(0, 0, 640, 688);
	clips.push_back(srcArea);
	horizontalScale = HOR_PS_STRAIGHT_TRACK;
	verticalScale = VER_PS_STRAIGHT_TRACK;
}

void StraightTrackView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(initialX + x - horizontalScale/2,
				  initialY + y - verticalScale/2, 
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea, (double) angle, SDL_FLIP_NONE);
}

