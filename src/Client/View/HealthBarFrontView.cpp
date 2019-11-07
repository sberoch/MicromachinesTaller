#include "HealthBarFrontView.h"
#include <iostream>

HealthBarFrontView::HealthBarFrontView(const SdlTexture& tex) : ObjectView(tex) {
	Area srcArea(0, 0, 2233, 368);
	clips.push_back(srcArea);
	horizontalScale = 300;
	verticalScale = 50;
	health = 100;
}

void HealthBarFrontView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(x - horizontalScale/2 + (100-health)/20,
				  y - verticalScale/2,
				  3*health,
				  verticalScale);
	texture.render(srcArea, destArea);
}

void HealthBarFrontView::resize(int newSize) {
	if (newSize > 0) {
		health = newSize;
	}
}