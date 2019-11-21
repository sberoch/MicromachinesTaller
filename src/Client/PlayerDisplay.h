#ifndef PLAYER_DISPLAY_H
#define PLAYER_DISPLAY_H

#include "SdlWindow.h"
#include "View/HealthBarBackView.h"
#include "View/HealthBarFrontView.h"
#include "View/MudSplatView.h"
#include "Audio.h"
#include "TextureCreator.h"
#include "View/NumberView.h"

class PlayerDisplay {
private:
	SdlWindow& window;
	Audio audio;

	TextureCreator creator;
	ObjectViewPtr lapsText;

	SdlTexture numbersTex;
	NumberView numberView;

	//TODO: creator para estos
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
	void setLapNumber(int lapNumber);
};

#endif // PLAYER_DISPLAY_H
