//
// Created by alvaro on 23/10/19.
//

#include <cstdint>
#include <netinet/in.h>
#include <vector>
#include <iostream>
#include <sstream>
#include "Protocol.h"
#include "SocketError.h"

#define FOUR_BYTES 4

Protocol::Protocol(Socket socket): socket(std::move(socket)) {}

Protocol::Protocol(Protocol&& other): socket(std::move(other.socket)) {}

Protocol::Protocol(const std::string& portName, const std::string& hostNumber){
    this->socket.connectToServer(portName, hostNumber);
}

std::string Protocol::receive(){
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

//Se envia la longitud como entero de 4 bytes y luego
//el mensaje verdadero
void Protocol::send(std::string message) {
    int messageLength = message.size();

    uint32_t number = htonl(messageLength);
    char *numberBuffer = (char*)&number;

    this->socket.send(numberBuffer, FOUR_BYTES);
    const char* messagePtr = message.c_str();
    this->socket.send(const_cast<char *>(messagePtr), messageLength);
}

void Protocol::forceShutDown() {
    this->socket.stop();
}

std::vector<std::string> Protocol::splitCommand(std::string &message,
                                                char delim) {
    std::string aux;
    std::stringstream fullLine(message);
    std::vector<std::string> strings;
    while (getline(fullLine, aux, delim)) {
        strings.push_back(aux);
    }
    return strings;
}

Protocol::~Protocol() = default;