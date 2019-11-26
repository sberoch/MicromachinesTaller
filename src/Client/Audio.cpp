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

	backgroundMusic = Mix_LoadMUS((SOUNDS_DIR + std::string("background.wav")).c_str());
	if(backgroundMusic == NULL) printf("%s\n", Mix_GetError());
	Mix_VolumeMusic(MIX_MAX_VOLUME/5);

	carEngine = Mix_LoadWAV((SOUNDS_DIR + std::string("car_engine.wav")).c_str());
	if (carEngine == NULL) printf("%s\n", Mix_GetError());
	effects.insert(std::make_pair(SFX_CAR_ENGINE, carEngine));

	carBrake = Mix_LoadWAV((SOUNDS_DIR + std::string("car_brake.wav")).c_str());
	if (carBrake == NULL) printf("%s\n", Mix_GetError());
	effects.insert(std::make_pair(SFX_CAR_BRAKE, carBrake));

	carExplosion = Mix_LoadWAV((SOUNDS_DIR + std::string("car_explosion.wav")).c_str());
	if (carExplosion == NULL) printf("%s\n", Mix_GetError());
	effects.insert(std::make_pair(SFX_CAR_EXPLOSION, carExplosion));

	carCollision = Mix_LoadWAV((SOUNDS_DIR + std::string("collision.wav")).c_str());
	if (carCollision == NULL) printf("%s\n", Mix_GetError());
	effects.insert(std::make_pair(SFX_CAR_COLLISION, carCollision));

	menuButton = Mix_LoadWAV((SOUNDS_DIR + std::string("menu_button.wav")).c_str());
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

void Audio::playEffect(SoundEffect effectID) {
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

void Audio::stopEffect(SoundEffect effectID) {
	if (effectID == SFX_CAR_ENGINE) {
		Mix_HaltChannel(CAR_ENGINE_CHANNEL);
	}
}

Audio::~Audio() {
	Mix_FreeMusic(backgroundMusic);
	backgroundMusic = NULL;
	Mix_FreeChunk(carBrake);
	Mix_FreeChunk(carCollision);
	Mix_FreeChunk(carExplosion);
	Mix_FreeChunk(carEngine);
	Mix_FreeChunk(menuButton);
	Mix_Quit();
}