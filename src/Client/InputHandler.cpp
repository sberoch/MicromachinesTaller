#include "InputHandler.h"
#include "../Common/Constants.h"
#include "../Common/Event/CommandEvent.h"
#include <iostream>

InputHandler::InputHandler(SdlWindow& window, Audio& audio, 
					SafeQueue<Event*>& sendQueue, int& clientId) :
	window(window),
	audio(audio),
	sendQueue(sendQueue),
	clientId(clientId) {
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
			//TODO: enviar especificacion de quien se va

		} else if (event.type == SDL_KEYDOWN) {
			SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
			switch (keyEvent.keysym.sym) {
				case SDLK_a: {
					//Turn left
					if (!left_pressed) {
						sendQueue.push(new CommandEvent(TURN_LEFT, clientId));
					}
					left_pressed = true;
					break;
				}
				case SDLK_d: {
					//Turn right
					if (!right_pressed) {
						sendQueue.push(new CommandEvent(TURN_RIGHT, clientId));
					}
					right_pressed = true;
					break;
				}
				case SDLK_w: {
					//Accelerate
					if (!up_pressed) {
						audio.playEffect(SFX_CAR_ENGINE);
						sendQueue.push(new CommandEvent(ACCELERATE, clientId));
					}
					up_pressed = true;
					break;
				}
				case SDLK_s: {
					//Brake
					if (!down_pressed) {
						audio.playEffect(SFX_CAR_BRAKE);
						sendQueue.push(new CommandEvent(DESACCELERATE, clientId));
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
			}
		} else if (event.type == SDL_KEYUP) {
			SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
			switch (keyEvent.keysym.sym) {
				case SDLK_a: {
					//Stop turning left
					if (left_pressed) {
						sendQueue.push(new CommandEvent(STOP_TURNING_LEFT, clientId));
					}
					left_pressed = false;
					break;
				}
				case SDLK_d: {
					//Stop turning right
					if (right_pressed) {
						sendQueue.push(new CommandEvent(STOP_TURNING_RIGHT, clientId));
					}
					right_pressed = false;
					break;
				}
				case SDLK_w: {
					//Stop accelerating
					if (up_pressed) {
						audio.stopEffect(SFX_CAR_ENGINE);
						sendQueue.push(new CommandEvent(STOP_ACCELERATING, clientId));
					}
					up_pressed = false;
					break;
				}
				case SDLK_s: {
					//Stop braking
					if (down_pressed) {
						sendQueue.push(new CommandEvent(STOP_DESACCELERATING, clientId));
					}
					down_pressed = false;
					break;
				}
			}
		}
	}
}
