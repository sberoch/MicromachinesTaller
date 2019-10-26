#ifndef SERVER_SNAPSHOT_H
#define SERVER_SNAPSHOT_H

#include <vector>
#include <map>
#include <string>

typedef std::vector<std::map<std::string, int>> CarList;

//TODO: protocolo/socket por argumento. Se sabe enviar y recibir

class ServerSnapshot {
private:
	CarList carList;
public:
	void setCar(int x, int y, int angle, int id);
	//void send(socket/protocolo)
	//void recv(socket/protocolo)
	const CarList& getCars();
};

#endif // SERVER_SNAPSHOT_H
