#include "TextureCreator.h"
#include <iostream>
#include "../Common/Constants.h"

#include "StraightTrackView.h"
#include "CurveTrackView.h"

TextureCreator::TextureCreator(const SdlWindow& window) :
	straightTrackTex("straight_track.png", window),
	curveTrackTex("curve_track.png", window) {
		idCounter = 0;
}

ObjectViewPtr TextureCreator::create(int type, int x, int y, int angle) {
	ObjectViewPtr ov;
	switch (type) {
		case ID_STRAIGHT_TRACK: ov.reset(new StraightTrackView(straightTrackTex, angle)); break;
		case ID_CURVE_TRACK: ov.reset(new CurveTrackView(curveTrackTex, angle)); break;
		default: throw std::runtime_error("Wrong view_id");
	}
	++idCounter;
	ov->setInitialPos(x, y);
	ov->setId(idCounter);
	return ov;
}