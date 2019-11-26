#include "LobbyWarningView.h"

#define WARNING_VIEW_CYCLES 80

LobbyWarningView::LobbyWarningView(const SdlTexture& tex) : 
	ObjectView(tex), _show(false), _showTimer(0) {
	Area srcArea(0, 0, 800, 400);
	clips.push_back(srcArea);
	horizontalScale = 400;
	verticalScale = 200;
}

void LobbyWarningView::drawAt(int x, int y) {
	Area srcArea = clips.front();
	Area destArea(x - horizontalScale/2,
				  y - verticalScale/2,
				  horizontalScale, verticalScale);
	texture.render(srcArea, destArea);
	_showTimer++;
	if (_showTimer > WARNING_VIEW_CYCLES) {
		_show = false;
	}
}

void LobbyWarningView::show() {
	_show = true;
	_showTimer = 0;
}

bool LobbyWarningView::showing() {
	return _show;
}
