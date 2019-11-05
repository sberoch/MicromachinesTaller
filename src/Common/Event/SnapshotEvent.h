#ifndef SERVER_SNAPSHOT_H
#define SERVER_SNAPSHOT_H

#include <vector>
#include <map>
#include <string>
#include "../Protocol.h"
#include "Event.h"

enum SnapshotGameEventType {
	ADD = 0,
	REMOVE = 1,
	ID_ASSIGN = 2
};

struct GameEventStruct {
	SnapshotGameEventType eventType;
	int objectType; //TODO: enum?
	float x;
	float y;
	int angle;
	int id;
};

struct CarStruct {
	float x;
	float y;
	int angle;
	int health;
	int id;
};

typedef std::vector<CarStruct> CarList;
typedef std::vector<GameEventStruct> GameEventsList;

class SnapshotEvent: public Event {
private:
	CarList carList;
	GameEventsList gameEventsList;
public:
	SnapshotEvent() = default;
	SnapshotEvent(Protocol &protocol);
    void send(Protocol &protocol) override;

	void setCar(float x, float y, int angle, int health, int id);
	const CarList& getCars();

	void setMap(json jMap);
	void setPlayerId(int id);

	void addGameItem(int type, float x, float y, int angle, int id);
	void removeGameItem(int type, int id);
	
	const GameEventsList& getGameEvents();
	
	virtual ~SnapshotEvent() = default;

private:
	void setGameEvent(SnapshotGameEventType eventType, 
			int objectType, float x, float y, int angle, int id);
};

#endif // SERVER_SNAPSHOT_H
