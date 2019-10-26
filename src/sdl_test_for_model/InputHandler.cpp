#include "InputHandler.h"

InputHandler::InputHandler(SdlWindow& window) :
	window(window) {
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

		} else if (event.type == SDL_KEYDOWN) {
			SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
			switch (keyEvent.keysym.sym) {
				case SDLK_a: {
					//Turn left
					break;
				}
				case SDLK_d: {
					//Turn right
					break;
				}
				case SDLK_w: {
					//Accelerate
					break;
				}
				case SDLK_F11:
					if (fullscreen) {
						window.setFullscreen(false);
						fullscreen = false;
					} else {
						window.setFullscreen(true);
						fullscreen = true;
					}
					break;
			}
		}
	}
}