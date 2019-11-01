#include "PlayerDisplay.h"

PlayerDisplay::PlayerDisplay(SdlWindow& window) : 
	healthBarBackTex("health_background.png", window),
	healthBackground(healthBarBackTex),
	healthBarFrontTex("health_bar.png", window),
	healthBar(healthBarFrontTex) {}

	