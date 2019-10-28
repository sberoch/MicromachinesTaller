#include "HealthBarBackView.h"

HealthBarBackView::HealthBarBackView(const SdlTexture& tex) {
	this->texture = tex;
	Area srcArea(0, 0, 2233, 368);
	clips.push_back(srcArea);
	horizontalScale = 300;
	verticalScale = 50;
}

void HealthBarBackView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(x - horizontalScale/2,
				  y - verticalScale/2,
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea);
}