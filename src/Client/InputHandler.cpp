#include "InputHandler.h"
#include "../Common/Constants.h"
#include "../Common/Event/CommandEvent.h"
#include <iostream>

InputHandler::InputHandler(SdlWindow& window, Audio& audio, ScreenRecorder& recorder,
						   SafeQueue<std::shared_ptr<Event>>& sendQueue, PlayerDescriptor& player) :
	window(window),
	audio(audio),
	recorder(recorder),
	sendQueue(sendQueue),
	player(player) {
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

		} else if (event.type == SDL_KEYDOWN) {
			SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
			switch (keyEvent.keysym.sym) {
				case SDLK_a: {
					//Turn left
					if (!left_pressed) {
						std::shared_ptr<Event> cmd(
								new CommandEvent(TURN_LEFT, player.globalId));
						sendQueue.push(cmd);
					}
					left_pressed = true;
					break;
				}
				case SDLK_d: {
					//Turn right
					if (!right_pressed) {
						std::shared_ptr<Event> cmd(
								new CommandEvent(TURN_RIGHT, player.globalId));
						sendQueue.push(cmd);
					}
					right_pressed = true;
					break;
				}
				case SDLK_w: {
					//Accelerate
					if (!up_pressed) {
						audio.playEffect(SFX_CAR_ENGINE);
						std::shared_ptr<Event> cmd(
								new CommandEvent(ACCELERATE, player.globalId));
						sendQueue.push(cmd);
					}
					up_pressed = true;
					break;
				}
				case SDLK_s: {
					//Brake
					if (!down_pressed) {
						audio.playEffect(SFX_CAR_BRAKE);
						std::shared_ptr<Event> cmd(
								new CommandEvent(DESACCELERATE, player.globalId));
						sendQueue.push(cmd);
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

				case SDLK_b: {
					player.isBot = true;
					break;
				}

				case SDLK_v: {
					if (!recorder.recording()) {
						recorder.start();
					} else {
						recorder.close();
					}
					break;
				}
			}
		} else if (event.type == SDL_KEYUP) {
			SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
			switch (keyEvent.keysym.sym) {
				case SDLK_a: {
					//Stop turning left
					if (left_pressed) {
						std::shared_ptr<Event> cmd(
								new CommandEvent(STOP_TURNING_LEFT, player.globalId));
						sendQueue.push(cmd);
					}
					left_pressed = false;
					break;
				}
				case SDLK_d: {
					//Stop turning right
					if (right_pressed) {
						std::shared_ptr<Event> cmd(
								new CommandEvent(STOP_TURNING_RIGHT, player.globalId));
						sendQueue.push(cmd);
					}
					right_pressed = false;
					break;
				}
				case SDLK_w: {
					//Stop accelerating
					if (up_pressed) {
						audio.stopEffect(SFX_CAR_ENGINE);
						std::shared_ptr<Event> cmd(
								new CommandEvent(STOP_ACCELERATING, player.globalId));
						sendQueue.push(cmd);
					}
					up_pressed = false;
					break;
				}
				case SDLK_s: {
					//Stop braking
					if (down_pressed) {
						std::shared_ptr<Event> cmd(
								new CommandEvent(STOP_DESACCELERATING, player.globalId));
						sendQueue.push(cmd);
					}
					down_pressed = false;
					break;
				}
			}
		}
	}
}
