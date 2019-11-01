#include "PlayerDisplay.h"

PlayerDisplay::PlayerDisplay(SdlWindow& window) : 
	healthBarBackTex("health_background.png", window),
	healthBackground(healthBarBackTex),
	healthBarFrontTex("health_bar.png", window),
	healthBar(healthBarFrontTex),
	cam_x(0), cam_y(0) {}

void PlayerDisplay::update(int cam_x, int cam_y, int health) {
	this->cam_x = cam_x;
	this->cam_Y = cam_y;
	healthBar.resize(health);
}

void PlayerDisplay::draw() {
	healthBackground.drawAt(xScreen*(0.8), yScreen*(0.9));
	healthBar.drawAt(xScreen*(0.8), yScreen*(0.9));
}