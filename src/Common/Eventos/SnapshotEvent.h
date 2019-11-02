#ifndef SERVER_SNAPSHOT_H
#define SERVER_SNAPSHOT_H

#include <vector>
#include <map>
#include <string>
#include "../Protocol.h"
#include "Event.h"

struct CarStruct {
	float x;
	float y;
	int angle;
	int health;
	int id;
};

typedef std::vector<CarStruct> CarList;

class SnapshotEvent: public Event {
private:
	CarList carList;
public:
    //Envia el estado de todos los autos.
    void send(Protocol &protocol, int id) override;

    void receive(Protocol &protocol) override ;

	void setCar(float x, float y, int angle, int health, int id);

	const CarList& getCars();
};

#endif // SERVER_SNAPSHOT_H
