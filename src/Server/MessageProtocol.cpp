//
// Created by alvaro on 28/9/19.
//

#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "MessageProtocol.h"
#define ONE_SIZE 1
#define FIRST_POSITION 0
#define END_OF_LINE '\n'

MessageProtocol::MessageProtocol(Socket skt): skt(std::move(skt)){}

//Hay que definir hasta cuando recibimos
std::string MessageProtocol::messageReceive() {
    std::vector<char> vec;
    char character[ONE_SIZE] = "";
    bool completeReceive = false;

    while (!completeReceive) {
        this->skt.receive(character, ONE_SIZE);
        char actualCharacter = character[FIRST_POSITION];

        completeReceive = (actualCharacter == END_OF_LINE);
        if (!completeReceive) {
            vec.push_back(actualCharacter);
        }
    }

    std::string str(vec.begin(), vec.end());
    return str;
}

//Podria ser util
std::vector<std::string> MessageProtocol::splitCommand(std::string &message,
                                                       char delim) {
    std::string aux;
    std::stringstream fullLine(message);
    std::vector<std::string> strings;
    while (getline(fullLine, aux, delim)) {
        strings.push_back(aux);
    }
    return strings;
}

//Hasta cuando enviar?
void MessageProtocol::messageSend(std::string& message) {
    message.push_back(END_OF_LINE);
    char *ptr = const_cast<char *>(message.c_str());

    this->skt.send(ptr, message.size());
}

void MessageProtocol::forceShutDown() {
    this->skt.stop();
}

MessageProtocol::~MessageProtocol() = default;

