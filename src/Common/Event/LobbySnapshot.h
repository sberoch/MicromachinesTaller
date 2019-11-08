#ifndef LOBBY_SNAPSHOT_H
#define LOBBY_SNAPSHOT_H

#include "Event.h"
#include "../Protocol.h"
#include <string>
#include <map>

struct RoomStruct {
	int id;
	bool gameStarted;
	std::vector<int> players;
};

typedef std::map<int, RoomStruct> RoomsMap;

class LobbySnapshot : public Event {
private:
	RoomsMap roomsMap;
public:
	LobbySnapshot() = default;
	LobbySnapshot(Protocol &protocol);
	virtual void send(Protocol &protocol) override;
	void sendId(int id);

	void createRoom(int room_id);
	void joinRoom(int player_id, int room_id);
	void startGame(int room_id);

	const RoomsMap& getRooms();

	virtual ~LobbySnapshot() = default;

private:
	void addRoom(int id, bool gameStarted, std::vector<int> players);
};

#endif // LOBBY_SNAPSHOT_H
