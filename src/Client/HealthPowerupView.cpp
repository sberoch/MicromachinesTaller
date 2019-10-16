#include "HealthPowerupView.h"

#define CANT_CLIPS 8

HealthPowerupView::HealthPowerupView(const SdlTexture& tex) {
	this->texture = tex;
	for (int i = 0; i < CANT_CLIPS; ++i) {
		Area area(i*102, 0, 102, 95);
		clips.push_back(area);
	}
	frame = 0;
	horizontalScale = 100;
	verticalScale = 100;
}

void HealthPowerupView::drawAt(int x, int y) {
	Area srcArea = clips.at(floor(frame/8));
	Area destArea(initialX + x - horizontalScale/2,
				  initialY + y - verticalScale/2, 
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea);
	++frame;
	if ((frame/8) >= CANT_CLIPS) {
		frame = 0;
	}
}