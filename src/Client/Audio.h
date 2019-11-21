#ifndef AUDIO_H
#define AUDIO_H 

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include "../Common/Constants.h"


class Audio {
private:
	Mix_Music* backgroundMusic = NULL;
	Mix_Chunk* carEngine = NULL;
	Mix_Chunk* carBrake = NULL;
	Mix_Chunk* carExplosion = NULL;
	Mix_Chunk* carCollision = NULL;
	Mix_Chunk* menuButton = NULL;

	std::map<SoundEffect, Mix_Chunk*> effects;
public:
	Audio();
	~Audio();
	void playMusic();
	void stopMusic();
	void playEffect(SoundEffect effectID);
	void stopEffect(SoundEffect effectID);
};

#endif