#include "TextureCreator.h"
#include <iostream>
#include "../Common/Constants.h"

#include "View/StraightTrackView.h"
#include "View/CurveTrackView.h"
#include "View/HealthPowerupView.h"
#include "View/BoostPowerupView.h"
#include "View/RockView.h"
#include "View/CarView.h"
#include "View/OilView.h"
#include "View/MudView.h"
#include "View/HealthBarBackView.h"
#include "View/HealthBarFrontView.h"

TextureCreator::TextureCreator(const SdlWindow& window) :
	straightTrackTex("straight_track.png", window),
	curveTrackTex("curve_track.png", window),
	powerupTex("powerups.png", window),
	rockTex("rock.png", window),
	car1Tex("car_1.png", window),
	car2Tex("car_2.png", window),
	car3Tex("car_3.png", window),
	car4Tex("car_4.png", window),
	oilTex("oil.png", window),
	mudTex("mud.png", window) {
		idCounter = 0;
}

ObjectViewPtr TextureCreator::create(int type, int x, int y, int angle) {
	ObjectViewPtr ov;
	switch (type) {
		case ID_STRAIGHT_TRACK: ov.reset(new StraightTrackView(straightTrackTex, angle)); break;
		case ID_CURVE_TRACK: ov.reset(new CurveTrackView(curveTrackTex, angle)); break;
		case ID_HEALTH_POWERUP: ov.reset(new HealthPowerupView(powerupTex)); break;
		case ID_BOOST_POWERUP: ov.reset(new BoostPowerupView(powerupTex)); break;
		case ID_ROCK: ov.reset(new RockView(rockTex)); break;
		case ID_CAR_1: ov.reset(new CarView(car1Tex, angle)); break;
		case ID_CAR_2: ov.reset(new CarView(car2Tex, angle)); break;
		case ID_CAR_3: ov.reset(new CarView(car3Tex, angle)); break;
		case ID_CAR_4: ov.reset(new CarView(car4Tex, angle)); break;
		case ID_OIL: ov.reset(new OilView(oilTex, angle)); break;
		case ID_MUD: ov.reset(new MudView(mudTex, angle)); break;
		default: throw std::runtime_error("Texture Creator: Wrong view_id");
	}
	++idCounter;
	ov->setInitialPos(x, y);
	ov->setId(idCounter);
	return ov;
}
