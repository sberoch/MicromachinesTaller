//
// Created by alvaro on 23/10/19.
//

#include <cstdint>
#include <netinet/in.h>
#include <vector>
#include <iostream>
#include "EventProtocol.h"
#include "../Common/SocketError.h"

#define FOUR_BYTES 4

std::string EventProtocol::receive(){
    int32_t ret = 0;
    char *data = (char*)&ret;

    //Recibo longitud en bytes.
    socket.receive(data, FOUR_BYTES);
    sscanf(data, "%d", &ret);
    int sizeIncoming = ntohl(ret);

    std::vector<char> vector(sizeIncoming);
    std::string auxiliar (vector.begin(), vector.end());
    char* buffer = const_cast<char *>(auxiliar.c_str());
    socket.receive(buffer, sizeIncoming);

    std::string message(buffer);

    return message;
}

EventProtocol::EventProtocol(Socket socket): socket(std::move(socket)) {}

EventProtocol::~EventProtocol() = default;

//Se envia la longitud como entero de 4 bytes y luego
//el mensaje verdadero
void EventProtocol::send(std::string message) {
    int messageLength = message.size();

    uint32_t number = htonl(messageLength);
    char *numberBuffer = (char*)&number;

    this->socket.send(numberBuffer, FOUR_BYTES);
    const char* messagePtr = message.c_str();
    this->socket.send(const_cast<char *>(messagePtr), messageLength);
}

void EventProtocol::forceShutDown() {
    this->socket.stop();
}
