#include "InputHandler.h"
#include "../Common/Constants.h"

InputHandler::InputHandler(SdlWindow& window, Audio& audio, 
					BlockingQueue& sendQueue) :
	window(window),
	audio(audio),
	sendQueue(sendQueue) {
	_done = false;
	fullscreen = true;
}

bool InputHandler::done() {
	return _done;
}

void InputHandler::handle() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			_done = true;
			sendQueue.push("clientQuit"); //TODO: especificar quien se va

		} else if (event.type == SDL_KEYDOWN) {
			SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
			switch (keyEvent.keysym.sym) {
				case SDLK_a: {
					//Turn left
					sendQueue.push("a");
					break;
				}
				case SDLK_d: {
					//Turn right
					sendQueue.push("d");
					break;
				}
				case SDLK_w: {
					//Accelerate
					audio.playEffect(SFX_CAR_ENGINE);
					sendQueue.push("w");
					break;
				}
				case SDLK_F11: {
					if (fullscreen) {
						window.setFullscreen(false);
						fullscreen = false;
					} else {
						window.setFullscreen(true);
						fullscreen = true;
					}
					break;
				}

				//Mock
				case SDLK_k: {
					audio.playEffect(SFX_CAR_EXPLOSION);
					break;
				}
				case SDLK_l: {
					audio.playEffect(SFX_BUTTON);
					break;
				}
			}
		} else if (event.type == SDL_KEYUP) {
			SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
			if (keyEvent.keysym.sym == SDLK_w) {
				audio.stopEffect(SFX_CAR_ENGINE);
			}
		}
	}
}