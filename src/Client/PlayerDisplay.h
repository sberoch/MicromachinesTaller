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
	void update(int cam_x, int cam_y, int health);
	void draw();
};

#endif // PLAYER_DISPLAY_H
