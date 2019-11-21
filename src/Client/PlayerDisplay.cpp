#include "PlayerDisplay.h"

#define SPLAT_CYCLES 80

PlayerDisplay::PlayerDisplay(SdlWindow& window) : 
	window(window),
	creator(window),

	numbersTex("numbers.png", window),
	numberView(numbersTex),

	healthBarBackTex("health_background.png", window),
	healthBackground(healthBarBackTex),
	healthBarFrontTex("health_bar.png", window),
	healthBar(healthBarFrontTex),

	splatTex("mud_splat.png", window),
	splat(splatTex),

	mudSplat(false), mudSplatTimer(0), health(100),
	cam_x(0), cam_y(0) {
	lapsText = creator.create(TYPE_LAPS_TEXT, 0, 0, 0);
}

void PlayerDisplay::update(int cam_x, int cam_y, int newHealth) {
	this->cam_x = cam_x;
	this->cam_y = cam_y;
	healthBar.resize(newHealth);
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

	healthBackground.drawAt(xScreen*(0.85), yScreen*(0.1));
	healthBar.drawAt(xScreen*(0.85), yScreen*(0.1));

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