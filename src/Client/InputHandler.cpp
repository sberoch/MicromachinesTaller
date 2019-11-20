#include "InputHandler.h"
#include "../Common/Constants.h"
#include "../Common/Event/CommandEvent.h"
#include <iostream>

InputHandler::InputHandler(SdlWindow& window, Audio& audio,
                           SafeQueue<Event*>& sendQueue, PlayerDescriptor& player) :
	window(window),
	audio(audio),
	sendQueue(sendQueue),
	player(player),
	_done(false),
	up_pressed(false),
	left_pressed(false),
	down_pressed(false),
	right_pressed(false) {}

bool InputHandler::done() {
	return _done;
}

void InputHandler::handle(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
		switch (keyEvent.keysym.sym) {
			case SDLK_a: {
				//Turn left
				if (!left_pressed) {
					sendQueue.push(new CommandEvent(TURN_LEFT, player.globalId));
				}
				left_pressed = true;
				break;
			}
			case SDLK_d: {
				//Turn right
				if (!right_pressed) {
					sendQueue.push(new CommandEvent(TURN_RIGHT, player.globalId));
				}
				right_pressed = true;
				break;
			}
			case SDLK_w: {
				//Accelerate
				if (!up_pressed) {
					audio.playEffect(SFX_CAR_ENGINE);
					sendQueue.push(new CommandEvent(ACCELERATE, player.globalId));
				}
				up_pressed = true;
				break;
			}
			case SDLK_s: {
				//Brake
				if (!down_pressed) {
					audio.playEffect(SFX_CAR_BRAKE);
					sendQueue.push(new CommandEvent(DESACCELERATE, player.globalId));
				}
				down_pressed = true;
				break;
			}

			case SDLK_b: {
				player.isBot = true;
				break;
			}
		}
	} else if (event.type == SDL_KEYUP) {
		SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
		switch (keyEvent.keysym.sym) {
			case SDLK_a: {
				//Stop turning left
				if (left_pressed) {
					sendQueue.push(new CommandEvent(STOP_TURNING_LEFT, player.globalId));
				}
				left_pressed = false;
				break;
			}
			case SDLK_d: {
				//Stop turning right
				if (right_pressed) {
					sendQueue.push(new CommandEvent(STOP_TURNING_RIGHT, player.globalId));
				}
				right_pressed = false;
				break;
			}
			case SDLK_w: {
				//Stop accelerating
				if (up_pressed) {
					audio.stopEffect(SFX_CAR_ENGINE);
					sendQueue.push(new CommandEvent(STOP_ACCELERATING, player.globalId));
				}
				up_pressed = false;
				break;
			}
			case SDLK_s: {
				//Stop braking
				if (down_pressed) {
					sendQueue.push(new CommandEvent(STOP_DESACCELERATING, player.globalId));
				}
				down_pressed = false;
				break;
			}
		}
	}
}
