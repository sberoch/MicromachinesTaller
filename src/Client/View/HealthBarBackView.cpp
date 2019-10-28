#include "HealthBarBackView.h"

HealthBarBackView::HealthBarBackView(const SdlTexture& tex) {
	this->texture = tex;
	Area srcArea(0, 0, 2233, 368);
	clips.push_back(srcArea);
	horizontalScale = 300;
	verticalScale = 50;
}

void HealthBarBackView::drawAt(int x, int y) {
	//Not affected by camera
	Area srcArea = clips.front();
	Area destArea(initialX - horizontalScale/2,
				  initialY - verticalScale/2,
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea);
}