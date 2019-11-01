#ifndef PLAYER_DISPLAY_H
#define PLAYER_DISPLAY_H

class PlayerDisplay {
private:
	SdlWindow& window;

	SdlTexture healthBarBackTex;
	HealthBarBackView healthBackground;
	SdlTexture healthBarFrontTex;
	HealthBarFrontView healthBar;
	
public:
	int cam_x, cam_y;
	PlayerDisplay(SdlWindow& window);
};

#endif // PLAYER_DISPLAY_H
