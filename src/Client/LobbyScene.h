
#ifndef LOBBY_SCENE_H
#define LOBBY_SCENE_H

#include "BaseScene.h"
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "../Common/SafeQueue.h"
#include "../Common/Event/Event.h"
#include "../Common/Event/LobbySnapshot.h"
#include "TextureCreator.h"
#include "Audio.h"
#include "View/BackgroundView.h"
#include "PlayerDescriptor.h"
#include <vector>


class LobbyScene : public BaseScene {
private:
    SdlWindow& window;
	SafeQueue<std::shared_ptr<Event>>& sendQueue;
	SafeQueue<std::shared_ptr<LobbySnapshot>>& lobbyRecvQueue;
    SdlTexture backgroundLobbyTex;
    BackgroundView backgroundLobby;
    Audio audio;
    TextureCreator creator;
    SDL_Event e;

    RoomsMap roomsMap;
    std::vector<ObjectViewPtr> roomViews;
    std::vector<ObjectViewPtr> playerViews;
    ObjectViewPtr arrow;
    ObjectViewPtr carSelected;

    bool _done;
    bool fullscreen;
    Scene nextScene;
    int xScreen, yScreen;
    PlayerDescriptor& player;

    int selectedRoom;
    int selectedPlayer;
    int joinedRoom;
    int joinedPlayer;
    std::vector<bool> startedRooms;

public:
    LobbyScene(SdlWindow& window, SafeQueue<std::shared_ptr<LobbySnapshot>>& lobbyRecvQueue,
			   SafeQueue<std::shared_ptr<Event>>& sendQueue, PlayerDescriptor& player);
    bool done() override;
    void update() override;
    void draw() override;
    Scene handle() override;
    ~LobbyScene() override = default;

private:
    void updateRooms(const RoomsMap& roomsMap);
    void drawRooms();
    void drawPlayers();
    void drawArrows();
    bool insidePlayButton(int x, int y);
    bool insideUserButton(int x, int y);
    bool insideBotButton(int x, int y);
    bool insideCreateRoomButton(int x, int y);
    bool insideJoinRoomButton(int x, int y);
    void checkInsideAnyRoom(int x, int y);
    void checkInsideAnyPlayer(int x, int y);
    void clearLobby();
};

#endif // LOBBY_SCENE_H
