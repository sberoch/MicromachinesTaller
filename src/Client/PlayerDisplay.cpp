#include "PlayerDisplay.h"

#define SPLAT_CYCLES 80

PlayerDisplay::PlayerDisplay(SdlWindow& window) : 
	window(window),

	healthBarBackTex("health_background.png", window),
	healthBackground(healthBarBackTex),
	healthBarFrontTex("health_bar.png", window),
	healthBar(healthBarFrontTex),

	splatTex("mud_splat.png", window),
	splat(splatTex),

	mudSplat(false), mudSplatTimer(0),
	cam_x(0), cam_y(0) {}

void PlayerDisplay::update(int cam_x, int cam_y, int health) {
	this->cam_x = cam_x;
	this->cam_y = cam_y;
	healthBar.resize(health);
}

void PlayerDisplay::draw() {
	int xScreen, yScreen;
	window.getWindowSize(&xScreen, &yScreen);

	healthBackground.drawAt(xScreen*(0.8), yScreen*(0.9));
	healthBar.drawAt(xScreen*(0.8), yScreen*(0.9));

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

void PlayerDisplay::showMudSplat() {
	mudSplatTimer = 0;
	mudSplat = true;
}