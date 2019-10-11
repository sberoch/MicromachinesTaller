#include "InputHandler.h"

InputHandler::InputHandler(SdlWindow& window) :
	window(window) {
	terminado = false;
	fullscreen = true;
}

bool InputHandler::termino() {
	return terminado;
}

void InputHandler::handle() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			terminado = true;

		} else if (event.type == SDL_KEYDOWN) {
			SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
			switch (keyEvent.keysym.sym) {
				case SDLK_a: {
					//Doblar izq
					break;
				}
				case SDLK_d: {
					//Doblar der
					break;
				}
				case SDLK_w: {
					//Acelerar
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