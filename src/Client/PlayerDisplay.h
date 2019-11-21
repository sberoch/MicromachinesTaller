#ifndef PLAYER_DISPLAY_H
#define PLAYER_DISPLAY_H

#include "SdlWindow.h"
#include "View/HealthBarBackView.h"
#include "View/HealthBarFrontView.h"
#include "View/MudSplatView.h"
#include "Audio.h"

class PlayerDisplay {
private:
	SdlWindow& window;
	Audio audio;

	SdlTexture healthBarBackTex;
	HealthBarBackView healthBackground;
	SdlTexture healthBarFrontTex;
	HealthBarFrontView healthBar;

	SdlTexture splatTex;
	MudSplatView splat;

	bool mudSplat;
	int mudSplatTimer;
	int health;

public:
	int cam_x, cam_y;
	PlayerDisplay(SdlWindow& window);
	void update(int cam_x, int cam_y, int newHealth);
	void draw();
	void showMudSplat();
};

#endif // PLAYER_DISPLAY_H
