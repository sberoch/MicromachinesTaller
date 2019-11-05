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
#include "View/ExplosionView.h"
#include "View/MudSplatView.h"

TextureCreator::TextureCreator(const SdlWindow& window) :
	straightTrackTex("straight_track.png", window),
	curveTrackTex("curve_track.png", window),
	powerupTex("powerups.png", window),
	rockTex("rock.png", window),
	carRedTex("car_red.png", window),
	carBlueTex("car_blue.png", window),
	carYellowTex("car_yellow.png", window),
	carGreenTex("car_green.png", window),
	oilTex("oil.png", window),
	mudTex("mud.png", window),
	explosionTex("explosion.png", window),
	mudSplatTex("mud_splat.png", window) {
		idCounter = 0;
}

ObjectViewPtr TextureCreator::create(int type, int x, int y, int angle) {
	ObjectViewPtr ov;
	switch (type) {
		case TYPE_STRAIGHT_TRACK: ov.reset(new StraightTrackView(straightTrackTex, angle)); break;
		case TYPE_CURVE_TRACK: ov.reset(new CurveTrackView(curveTrackTex, angle)); break;
		case TYPE_HEALTH_POWERUP: ov.reset(new HealthPowerupView(powerupTex)); break;
		case TYPE_BOOST_POWERUP: ov.reset(new BoostPowerupView(powerupTex)); break;
		case TYPE_ROCK: ov.reset(new RockView(rockTex)); break;
		case TYPE_CAR_RED: ov.reset(new CarView(carRedTex, angle)); break;
		case TYPE_CAR_BLUE: ov.reset(new CarView(carBlueTex, angle)); break;
		case TYPE_CAR_YELLOW: ov.reset(new CarView(carYellowTex, angle)); break;
		case TYPE_CAR_GREEN: ov.reset(new CarView(carGreenTex, angle)); break;
		case TYPE_OIL: ov.reset(new OilView(oilTex, angle)); break;
		case TYPE_MUD: ov.reset(new MudView(mudTex, angle)); break;
		case TYPE_EXPLOSION: ov.reset(new ExplosionView(explosionTex)); break;
		case TYPE_MUD_SPLAT: ov.reset(new MudSplatView(mudSplatTex)); break;
		default: throw std::runtime_error("Texture Creator: Wrong view_id");
	}
	++idCounter;
	ov->setInitialPos(x, y);
	ov->setId(idCounter);
	return ov;
}
