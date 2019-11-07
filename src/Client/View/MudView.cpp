#include "MudView.h"

MudView::MudView(const SdlTexture& tex, const int& angle) :
	ObjectView(tex), angle(angle) {
	Area srcArea(0, 0, 871, 374);
	clips.push_back(srcArea);
	horizontalScale = HOR_PS_MUD;
	verticalScale = VER_PS_MUD;
}

void MudView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(initialX + x - horizontalScale/2,
				  initialY + y - verticalScale/2, 
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea, (double) angle, SDL_FLIP_NONE);
}