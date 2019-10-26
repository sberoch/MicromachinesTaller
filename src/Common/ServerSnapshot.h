#ifndef SERVER_SNAPSHOT_H
#define SERVER_SNAPSHOT_H

#include <vector>
#include <map>
#include <string>
#include "../Server/Protocol.h"


struct Car {
	float x;
	float y;
	int angle;
	int id;
};

typedef std::vector<Car> CarList;

//TODO: protocolo/socket por argumento. Se sabe enviar y recibir

class ServerSnapshot {
private:
	CarList carList;
public:
    //Hace un receive interno.
    explicit ServerSnapshot(Protocol& protocol);

	void setCar(float x, float y, int angle, int id);

	const CarList& getCars();

	//Envia el estado de todos los autos.
	void send(Protocol& protocol);
};

#endif // SERVER_SNAPSHOT_H
