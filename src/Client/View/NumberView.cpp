#include <iostream>
#include "NumberView.h"

NumberView::NumberView(const SdlTexture &tex) :
	ObjectView(tex),
	_number(0){

	for (int i = 0; i < 5; ++i) {
		Area area(i*120, 0, 120, 120);
		clips.push_back(area);
	}
	for(int i = 0; i < 5; ++i) {
		Area area(i*120, 120, 120, 120);
		clips.push_back(area);
	}

	horizontalScale = 65;
	verticalScale = 65;
}

void NumberView::setNumber(int number) {
	_number = number;
}

void NumberView::drawAt(int x, int y) {
	Area srcArea = clips.at(_number);
	Area destArea(x - horizontalScale/2,
				  y - verticalScale/2,
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea);
}
