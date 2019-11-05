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

	void addStraightTrack(float x, float y, int angle, int id);
	void addCurveTrack(float x, float y, int angle, int id);
	void addRock(float x, float y, int id);
	void addOil(float x, float y, int angle, int id);
	void addMud(float x, float y, int angle, int id);
	void addHealthPowerup(float x, float y, int id);
	void addBoostPowerup(float x, float y, int id);
	void addExplosion(float x, float y);
	const GameEventsList& getGameEvents();
	
	virtual ~SnapshotEvent() = default;

private:
	void setGameEvent(SnapshotGameEventType eventType, 
			int objectType, float x, float y, int angle, int id);
};

#endif // SERVER_SNAPSHOT_H
