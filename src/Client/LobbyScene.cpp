#include "LobbyScene.h"
#include "../Common/Event/EnterRoomEvent.h"
#include "../Common/Event/CreateRoomEvent.h"
#include "../Common/Event/PlayEvent.h"

LobbyScene::LobbyScene(SdlWindow& window, SafeQueue<std::shared_ptr<LobbySnapshot>>& lobbyRecvQueue,
					   SafeQueue<std::shared_ptr<Event>>& sendQueue, PlayerDescriptor& player) :
        window(window),
        lobbyRecvQueue(lobbyRecvQueue),
        sendQueue(sendQueue),
        backgroundLobbyTex("lobby.png", window),
        backgroundLobby(backgroundLobbyTex),
        creator(window),
        _done(false),
        fullscreen(true),
        nextScene(SCENE_LOBBY),

        selectedRoom(-1),
        selectedPlayer(-1),
        joinedRoom(-1),
        joinedPlayer(-1),
        player(player) {
    roomViews.push_back(creator.create(TYPE_ROOM_1, 0, 0, 0));
    roomViews.push_back(creator.create(TYPE_ROOM_2, 0, 0, 0));
    roomViews.push_back(creator.create(TYPE_ROOM_3, 0, 0, 0));
    roomViews.push_back(creator.create(TYPE_ROOM_4, 0, 0, 0));

    playerViews.push_back(creator.create(TYPE_CAR_RED, 0, 0, 270));
    playerViews.push_back(creator.create(TYPE_CAR_BLUE, 0, 0, 270));
    playerViews.push_back(creator.create(TYPE_CAR_YELLOW, 0, 0, 270));
    playerViews.push_back(creator.create(TYPE_CAR_GREEN, 0, 0, 270));

    arrow = creator.create(TYPE_ARROW, 0, 0, 0);
    carSelected = creator.create(TYPE_CAR_SELECTED, 0, 0, 270);
}

bool LobbyScene::done() {
    return _done;
}

void LobbyScene::update() {
    nextScene = SCENE_LOBBY;

    window.getWindowSize(&xScreen, &yScreen);
    backgroundLobby.setDims(xScreen, yScreen);

    std::shared_ptr<LobbySnapshot> snap;
    while (lobbyRecvQueue.get(snap)) {
    	player.globalId = snap->getMyId();
    	updateRooms(snap->getRooms());
    }
}

void LobbyScene::updateRooms(const RoomsMap& roomsMap) {
    this->roomsMap = roomsMap;
    bool gameStartedWithMeInIt = false;

    //Check if any game started and if i'm in it.
    for (auto& room : roomsMap) {
        if (room.second.gameStarted) {
            for (auto& playerId : room.second.players) {
                if (playerId == player.globalId) {
                    gameStartedWithMeInIt = true;
                    break;
                }
            }
        }
    }

    if (gameStartedWithMeInIt) {
        clearLobby();
    }
}

void LobbyScene::draw() {
    window.fill();
    backgroundLobby.drawAt(xScreen/2, yScreen/2);
    drawRooms();
    drawPlayers();
    drawArrows();
    window.render();
}

void LobbyScene::drawRooms() {
    for (int i = 0; i < roomsMap.size(); ++i) {
        roomViews.at(i)->drawAt(0.26*xScreen, (0.22 + 0.1*i)*yScreen);
    }
}

void LobbyScene::drawPlayers() {
    if (selectedRoom != -1) {
        for (int i = 0; i < 4; ++i) {
            playerViews.at(i)->drawAt(0.76*xScreen, (0.22 + 0.1*i)*yScreen);
        }
        std::vector<bool> selectedCars = roomsMap.at(selectedRoom).selectedCars;
        for (int i = 0; i < 4; ++i) {
            if (selectedCars.at(i)) {
                carSelected->drawAt(0.76*xScreen, (0.22 + 0.1*i)*yScreen);
            }
        }
    }
}

void LobbyScene::drawArrows() {
    if (selectedRoom != -1) {
        arrow->drawAt(0.12*xScreen, (0.22 + 0.1*selectedRoom)*yScreen);
    }
    if (selectedPlayer != -1) {
        arrow->drawAt(0.62*xScreen, (0.22 + 0.1*selectedPlayer)*yScreen);
    }
}

Scene LobbyScene::handle() {
    while (SDL_PollEvent(&e) && !_done) {
        if (e.type == SDL_QUIT) {
            _done = true;

        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (insidePlayButton(x, y)) {
                if (!roomsMap.empty() && selectedRoom != -1 && joinedRoom != -1) {
					std::shared_ptr<Event> cmd(new PlayEvent(player.globalId));
                    sendQueue.push(cmd);
                    audio.playEffect(SFX_BUTTON);
                    nextScene = SCENE_GAME;
                    clearLobby();
                }
            }
            else if (insideUserButton(x, y)) {
                player.isBot = false;
                audio.playEffect(SFX_BUTTON);
            }
            else if (insideBotButton(x, y)) {
                player.isBot = true;
                audio.playEffect(SFX_BUTTON);
            }
            else if (insideCreateRoomButton(x, y)) {
                if (roomsMap.size() < 4) {
					std::shared_ptr<Event> cmd(new CreateRoomEvent());
					sendQueue.push(cmd);
                    audio.playEffect(SFX_BUTTON);
                }
            }
            else if (insideJoinRoomButton(x, y)) {
                if (!roomsMap.empty() && selectedRoom != -1 && selectedPlayer != -1) {
                    joinedRoom = selectedRoom;
                    joinedPlayer = selectedPlayer;
                    audio.playEffect(SFX_BUTTON);
					std::shared_ptr<Event> cmd(new EnterRoomEvent(
													player.globalId,
													selectedRoom,
													joinedPlayer));
					sendQueue.push(cmd);
                    player.playerId = joinedPlayer;
                }
            } else {
                checkInsideAnyRoom(x, y);
                checkInsideAnyPlayer(x, y);
            }

        } else if (e.type == SDL_KEYDOWN) {
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) e;
            if (keyEvent.keysym.sym == SDLK_F11) {
                if (fullscreen) {
                    window.setFullscreen(false);
                    fullscreen = false;
                } else {
                    window.setFullscreen(true);
                    fullscreen = true;
                }
            }
        }
    }
    return nextScene;
}

bool LobbyScene::insidePlayButton(int x, int y) {
    Area btn(0.4*xScreen, 0.8*yScreen, 0.2*xScreen, 0.15*yScreen);
    return btn.isInside(x, y);
}

bool LobbyScene::insideUserButton(int x, int y) {
    Area btn(0.7*xScreen, 0.75*yScreen, 0.3*xScreen, 0.1*yScreen);
    return btn.isInside(x, y);
}

bool LobbyScene::insideBotButton(int x, int y) {
    Area btn(0.7*xScreen, 0.87*yScreen, 0.3*xScreen, 0.1*yScreen);
    return btn.isInside(x, y);
}

bool LobbyScene::insideCreateRoomButton(int x, int y) {
    Area btn(0, 0.75*yScreen, 0.3*xScreen, 0.1*yScreen);
    return btn.isInside(x, y);
}

bool LobbyScene::insideJoinRoomButton(int x, int y) {
    Area btn(0, 0.87*yScreen, 0.3*xScreen, 0.1*yScreen);
    return btn.isInside(x, y);
}

void LobbyScene::checkInsideAnyRoom(int x, int y) {
    for (int i = 0; i < roomsMap.size(); ++i) {

        Area btn(0.15*xScreen, (0.17 + 0.1*i)*yScreen, 0.2*xScreen, 0.1*yScreen);

        if (btn.isInside(x, y)) {
            if (joinedRoom == i) {
                selectedPlayer = joinedPlayer;
            } else {
                selectedPlayer = -1;
            }
            
            audio.playEffect(SFX_BUTTON);
            selectedRoom = i;
        }
    }
}

void LobbyScene::checkInsideAnyPlayer(int x, int y) {
    for (int i = 0; i < 4; ++i) {

        Area btn(0.65*xScreen, (0.17 + 0.1*i)*yScreen, 0.2*xScreen, 0.1*yScreen);
        if (selectedRoom != -1) {
            bool alreadyPicked = roomsMap.at(selectedRoom).selectedCars.at(i);
            bool canChange = (joinedPlayer == -1) || (joinedRoom != selectedRoom);

            if (btn.isInside(x, y) && !alreadyPicked && canChange) {
                audio.playEffect(SFX_BUTTON);
                selectedPlayer = i;
            }
        }
    }
}

void LobbyScene::clearLobby() {
    selectedRoom = -1;
    selectedPlayer = -1;
    joinedRoom = -1;
    joinedPlayer = -1;
    this->roomsMap.clear();
    lobbyRecvQueue.clear();
}
