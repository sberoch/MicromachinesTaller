#ifndef SERVER_SNAPSHOT_H
#define SERVER_SNAPSHOT_H

#include <vector>
#include <map>
#include <list>
#include <string>
#include "../Protocol.h"
#include "Event.h"

enum SnapshotGameEventType {
	ADD = 0,
	REMOVE = 1,
    MAP_LOAD_FINISHED = 2,
	MUD_SPLAT = 3,
	GAME_OVER = 4,
	ID_ASSIGN = 5
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

typedef std::list<CarStruct> CarStructList;
typedef std::vector<GameEventStruct> GameEventsList;

class SnapshotEvent: public Event {
private:
	CarStructList carStructList;
	GameEventsList gameEventsList;
public:
	SnapshotEvent() = default;
	SnapshotEvent(SnapshotEvent& other);
	explicit SnapshotEvent(Protocol &protocol);
    void send(Protocol &protocol) override;

	void setCar(float x, float y, int angle, int health, int id);
	const CarStructList& getCars();
	
    void setMap(const json& jMap);


	void addGameItem(int type, float x, float y, int angle, int id);
	void removeGameItem(int type, int id);
	void signalMapReady();
	void setMudSplatEvent();
	void setGameOver();
	
	const GameEventsList& getGameEvents();

    void setPlayerId(int id);

	virtual ~SnapshotEvent() = default;

private:
	void setGameEvent(SnapshotGameEventType eventType, 
			int objectType, float x, float y, int angle, int id);

    CarStruct findCar(int id);

    bool isThereACar(int id);
};

#endif // SERVER_SNAPSHOT_H
