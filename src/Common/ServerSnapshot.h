#ifndef SERVER_SNAPSHOT_H
#define SERVER_SNAPSHOT_H

#include <vector>
#include <map>
#include <string>


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
	void setCar(float x, float y, int angle, int id);
	//void send(socket/protocolo)
	//void recv(socket/protocolo)
	const CarList& getCars();
};

#endif // SERVER_SNAPSHOT_H
