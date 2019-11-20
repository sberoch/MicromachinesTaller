#include "SceneSelector.h"
#include "../Common/Constants.h"
#include "../Common/SocketError.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "LobbyScene.h"
#include "EndScene.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

SceneSelector::SceneSelector(int xScreen, int yScreen,
		const std::string& host, const std::string& port) : 
	window(xScreen, yScreen),
	currentScene(SCENE_MENU),
	done(false),
	fullscreen(true),
	protocol(host, port),
	sendQueue(true),
	receiver(gameRecvQueue, lobbyRecvQueue, endRecvQueue, protocol, currentScene),
	sender(sendQueue, protocol) {
		scenes.insert(std::make_pair(SCENE_MENU, new MenuScene(window, sendQueue)));
		scenes.insert(std::make_pair(SCENE_LOBBY, new LobbyScene(window, lobbyRecvQueue, sendQueue, player)));
		scenes.insert(std::make_pair(SCENE_GAME, new GameScene(window, gameRecvQueue, sendQueue, player)));
		scenes.insert(std::make_pair(SCENE_END, new EndScene(window, endRecvQueue)));
		
		receiver.start();
		sender.start();
	}

void SceneSelector::run() {
	BaseScene* scene;
	try {
		while(!receiver.finished() && !sender.finished()) {
			std::clock_t begin = clock();

		    if (currentScene != 0) {
		    	scene = scenes.at(currentScene);
				scene->update();
				scene->draw();
				currentScene = handle(scene);
				if (done || scene->done()) {
					protocol.forceShutDown(); //No estoy seguro de que vaya aca
				}
		    }

		    //Check exec time and sleep
		    std::clock_t end = clock();
		    double execTime = double(end - begin) / (CLOCKS_PER_SEC/1000);
		    if (execTime < 25) this->sleep(25 - execTime);
	    }
	} catch (SocketError& se) {
		std::cerr << "Socket error captured in SceneSelector" << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Excepction from scene selector: " << e.what() << std::endl;
	} catch (...){
        std::cerr << "Unknown error from scene selector" << std::endl;
    }
}

int SceneSelector::handle(BaseScene* scene) {
    //Handle events common to all scenes
    while (SDL_PollEvent(&event) && !done) {
        if (event.type == SDL_QUIT) {
            done = true;
            return currentScene;

        } else if (event.type == SDL_KEYDOWN) {
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
            if (keyEvent.keysym.sym == SDLK_F11) {
                if (fullscreen) {
                    window.setFullscreen(false);
                    fullscreen = false;
                } else {
                    window.setFullscreen(true);
                    fullscreen = true;
                }
                return currentScene;
            }
        }
		return scene->handle(event);
    }
}

void SceneSelector::sleep(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

SceneSelector::~SceneSelector() {
	receiver.join();
	sendQueue.push(nullptr);
	sender.join();

	for (auto& it : scenes) {
		delete it.second;
	}
}
