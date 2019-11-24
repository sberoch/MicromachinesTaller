#include "PlayerDisplay.h"

PlayerDisplay::PlayerDisplay(SdlWindow& window) : 
	window(window),
	creator(window),

	numbersTex("numbers.png", window),
	numberView(numbersTex),

	splatTex("mud_splat.png", window),
	splat(splatTex),

	mudSplat(false),
	mudSplatTimer(0),
	health(100),
	exploded(false),
	carExplodedTimer(0),
	cam_x(0), cam_y(0) {
	lapsText = creator.create(TYPE_LAPS_TEXT, 0, 0, 0);
	healthBackground = creator.create(TYPE_HEALTH_BAR_BACK, 0, 0, 0);
	healthBar = creator.create(TYPE_HEALTH_BAR_FRONT, 0, 0, 0);
}

void PlayerDisplay::update(int cam_x, int cam_y, int newHealth) {
	if (!exploded) {
		this->cam_x = cam_x;
		this->cam_y = cam_y;

	} else {
		carExplodedTimer++;
		if (carExplodedTimer >= CAR_EXPLOSION_PENALTY) {
			carExplodedTimer = 0;
			exploded = false;
		}
	}
	healthBar->resize(newHealth);
	if (newHealth < health) {
		audio.playEffect(SFX_CAR_COLLISION);
	}
	health = newHealth;
}

void PlayerDisplay::draw() {
	int xScreen, yScreen;
	window.getWindowSize(&xScreen, &yScreen);

	lapsText->drawAt(xScreen*(0.1), yScreen*(0.1));
	numberView.drawAt(xScreen*(0.18), yScreen*(0.1));

	healthBackground->drawAt(xScreen*(0.85), yScreen*(0.1));
	healthBar->drawAt(xScreen*(0.85), yScreen*(0.1));

	if (mudSplat) {
		splat.setDims(xScreen, yScreen);
		splat.drawAt(xScreen/2, yScreen/2);
		mudSplatTimer++;
	}

	if (mudSplatTimer >= SPLAT_CYCLES) {
		mudSplat = false;
		mudSplatTimer = 0;
	}
}

void PlayerDisplay::setLapNumber(int lapNumber) {
	numberView.setNumber(lapNumber);
}

void PlayerDisplay::showMudSplat() {
	mudSplatTimer = 0;
	mudSplat = true;
}

void PlayerDisplay::carExploded(int exp_x, int exp_y) {
	this->cam_x = exp_x;
	this->cam_y = exp_y;
	carExplodedTimer = 0;
	exploded = true;
}

bool PlayerDisplay::hasMyCarExploded() {
	return exploded;
}


void PlayerDisplay::clear() {
	this->cam_x = 0;
	this->cam_y = 0;
	carExplodedTimer = 0;
	exploded = false;
	mudSplatTimer = 0;
	mudSplat = false;
	numberView.setNumber(0);
	health = 100;
}

