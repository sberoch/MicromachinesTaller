#include "InputHandler.h"
#include "../Common/Constants.h"

InputHandler::InputHandler(SdlWindow& window, Audio& audio, 
					BlockingQueue& sendQueue) :
	window(window),
	audio(audio),
	sendQueue(sendQueue) {
	_done = false;
	fullscreen = true;
	up_pressed = false;
	left_pressed = false;
	down_pressed = false;
	right_pressed = false;
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
					if (!left_pressed) {
						sendQueue.push("a");
					}
					left_pressed = true;
					break;
				}
				case SDLK_d: {
					//Turn right
					if (!right_pressed) {
						sendQueue.push("d");
					}
					right_pressed = true;
					break;
				}
				case SDLK_w: {
					//Accelerate
					if (!up_pressed) {
						audio.playEffect(SFX_CAR_ENGINE);
						sendQueue.push("w");
					}
					up_pressed = true;
					break;
				}
				case SDLK_s: {
					//Break
					if (!down_pressed) {
						audio.playEffect(SFX_CAR_BRAKE);
						sendQueue.push("s");
					}
					down_pressed = true;
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
			switch (keyEvent.keysym.sym) {
				case SDLK_a: {
					//Stop turning left
					if (left_pressed) {
						sendQueue.push("a_stop");
					}
					left_pressed = false;
					break;
				}
				case SDLK_d: {
					//Stop turning right
					if (right_pressed) {
						sendQueue.push("d_stop");
					}
					right_pressed = false;
					break;
				}
				case SDLK_w: {
					//Stop accelerating
					if (up_pressed) {
						audio.stopEffect(SFX_CAR_ENGINE);
						sendQueue.push("w_stop");
					}
					up_pressed = false;
					break;
				}
				case SDLK_s: {
					//Stop braking
					if (down_pressed) {
						sendQueue.push("s_stop");
					}
					down_pressed = false;
					break;
				}
			}
		}
	}
}
