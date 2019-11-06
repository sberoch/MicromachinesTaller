#include "Audio.h"
#include "../Common/Constants.h"
#include <iostream>

#define CAR_ENGINE_CHANNEL 10

Audio::Audio() {
	if(SDL_Init(SDL_INIT_AUDIO) < 0) { 
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError()); 
	}
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	Mix_AllocateChannels(16);

	backgroundMusic = Mix_LoadMUS("./background.mp3");
	if(backgroundMusic == NULL) {
	    printf("asdfasdfasdf");
	    printf("%s\n", Mix_GetError());
	}
	Mix_VolumeMusic(MIX_MAX_VOLUME/5);

	carEngine = Mix_LoadWAV("car_engine.wav");
	if (carEngine == NULL) printf("%s\n", Mix_GetError());
	effects.insert(std::make_pair(SFX_CAR_ENGINE, carEngine));

	carBrake = Mix_LoadWAV("car_brake.wav");
	if (carBrake == NULL) printf("%s\n", Mix_GetError());
	effects.insert(std::make_pair(SFX_CAR_BRAKE, carBrake));

	carExplosion = Mix_LoadWAV("car_explosion.wav");
	if (carExplosion == NULL) printf("%s\n", Mix_GetError());
	effects.insert(std::make_pair(SFX_CAR_EXPLOSION, carExplosion));

	menuButton = Mix_LoadWAV("menu_button.wav");
	if (menuButton == NULL) printf("%s\n", Mix_GetError());
	effects.insert(std::make_pair(SFX_BUTTON, menuButton));
}

void Audio::playMusic() {
	if(Mix_PlayingMusic() == 0) {
		Mix_FadeInMusic(backgroundMusic, -1, 3000);
	}
}

void Audio::stopMusic() {
	Mix_HaltMusic();
}

void Audio::playEffect(int effectID) {
	Mix_Chunk* effect = effects.at(effectID);
	if (effectID == SFX_CAR_ENGINE) {
		//Played undefined ammount of time
		// in specific channel so it can be later halted
		if (Mix_Playing(CAR_ENGINE_CHANNEL) == 0) {
			Mix_PlayChannel(CAR_ENGINE_CHANNEL, effect, -1);
		}
	} else {
		Mix_PlayChannel(-1, effect, 0);
	}
}

void Audio::stopEffect(int effectID) {
	if (effectID == SFX_CAR_ENGINE) {
		Mix_HaltChannel(CAR_ENGINE_CHANNEL);
	}
}

Audio::~Audio() {
	Mix_FreeMusic(backgroundMusic);
	backgroundMusic = NULL;
	for (auto& it : effects) {
		delete it.second;
	}
	Mix_Quit();
}