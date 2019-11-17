#ifndef LOBBY_SNAPSHOT_H
#define LOBBY_SNAPSHOT_H

#include "Event.h"
#include "../Protocol.h"
#include <string>
#include <map>
#include <list>

struct RoomStruct {
	int id;
	bool gameStarted;
	std::list<int> players;
	std::vector<bool> selectedCars = {false, false, false, false};
};

typedef std::map<int, RoomStruct> RoomsMap;

class LobbySnapshot : public Event {
private:
	RoomsMap roomsMap;
	int actualClientId;
public:
	LobbySnapshot() = default;

    LobbySnapshot(Protocol &protocol);
    LobbySnapshot(LobbySnapshot& other);
	virtual void send(Protocol &protocol) override;

	void createRoom(int room_id);
	void joinRoom(int player_id, int room_id);
	void startGame(int room_id);
	void addSelectedCar(int room_id, int player_room_id);

	const RoomsMap& getRooms();
	int getMyId();
	bool gameStarted(int player_id);

	virtual ~LobbySnapshot() = default;
    void setPlayerId(int id);

private:
	void addRoom(int id, bool gameStarted, std::list<int> players, std::vector<bool> selectedCars);

    void removeIdFromOldRoom(int player_id);
};

#endif // LOBBY_SNAPSHOT_H
