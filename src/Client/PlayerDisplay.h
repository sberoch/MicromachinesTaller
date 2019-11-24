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
	ObjectViewPtr healthBackground;
	ObjectViewPtr healthBar;

	SdlTexture numbersTex;
	NumberView numberView;

	SdlTexture splatTex;
	MudSplatView splat;

	bool mudSplat;
	int mudSplatTimer;
	int health;
	bool exploded;
	int carExplodedTimer;

public:
	int cam_x, cam_y;
	explicit PlayerDisplay(SdlWindow& window);
	void update(int cam_x, int cam_y, int newHealth);
	void draw();
	void showMudSplat();
	void setLapNumber(int lapNumber);
	void carExploded(int exp_x, int exp_y);
	void clear();
	bool hasMyCarExploded();
};

#endif // PLAYER_DISPLAY_H
