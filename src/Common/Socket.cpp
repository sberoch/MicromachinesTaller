
//
// Created by alvaro on 27/9/19.
//

#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <iostream>
#include "Socket.h"
#include "SocketError.h"

Socket::Socket() {
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
}

Socket::Socket(int fd) {
    this->fd = fd;
}


Socket::Socket(Socket&& other) noexcept {
    this->fd = other.fd;
    other.fd = -1;
}

void Socket::stop(){
    shutdown(this->fd, SHUT_RDWR);
    close(this->fd);
}

Socket::~Socket(){
    if (this->fd != -1) {
        shutdown(this->fd, SHUT_RDWR);
        close(this->fd);
    }
}

void Socket::setHintsForServer(void* addrinfo){
    auto *hints = (struct addrinfo*) addrinfo;
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;
}

void Socket::setServerReady(const char* portNumber) {
    struct addrinfo hints{};
    struct addrinfo *results;
    struct addrinfo *ptr;
    bool connected = false;

    setHintsForServer(&hints);

    int s = getaddrinfo(nullptr, portNumber, &hints, &results);
    if (s != 0){
        throw std::runtime_error("Error en getaddrinfo");
    }

    for (ptr = results; ptr != nullptr && !connected; ptr = ptr->ai_next) {
        this->fd = socket(ptr->ai_family,
                          ptr->ai_socktype, ptr->ai_protocol);
        if (this->fd == -1){
            throw std::runtime_error("Error al obtener Socket");
        }

        int val = 1;
        setsockopt(this->fd,
                   SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));

        s = bind(this->fd, ptr->ai_addr, ptr->ai_addrlen);
        if (s == -1){
            throw std::runtime_error("Error al bindear con el cliente");
        }
        connected = (s != -1);
    }
    freeaddrinfo(results);
    listen();
}

void Socket::listen(){
    int connectionsAllowed = SOMAXCONN;
    int result = ::listen(this->fd, connectionsAllowed);
    if (result == -1){
        throw std::runtime_error("Error en la operacion listen");
    }
}

Socket Socket::accept(){
    struct sockaddr clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);
    int socketFd = ::accept(this->fd, &clientAddress, &clientAddressLength);
    if (socketFd == -1){
        throw SocketError();
    }

    return std::move(Socket(socketFd));
}

void Socket::send(char *buffer, int messageLength){
    int bytesSent = 0;
    while (messageLength > 0){
        bytesSent = ::send(this->fd, buffer, messageLength, MSG_NOSIGNAL);
        if (bytesSent < 0){
            throw std::runtime_error("Error al enviar mensaje");
        }
        buffer += bytesSent;
        messageLength -= bytesSent;
    }
}


void Socket::receive(char *buffer, int length){
    int r = 0;

    while (length > 0){
        r = ::recv(this->fd, buffer, length, 0);
        if (r == 0){
            throw SocketError();
        }
        if (r == -1){
            throw SocketError();
        }
        buffer += r;
        length -= r;
    }
}

void Socket::connectToServer(const std::string& hostName,
                             const std::string& portNumber){
    struct addrinfo hints{};
    int s = 0;
    struct addrinfo *ai_list;
    struct addrinfo *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    char* host = const_cast<char *>(hostName.c_str());
    char* port = const_cast<char *>(portNumber.c_str());
    s = getaddrinfo(host, port, &hints, &ai_list);
    if (s != 0){
        throw std::runtime_error("Error en la operacion getaddrInfo");
    }
    bool connected = false;
    for (ptr = ai_list; ptr != nullptr && !connected; ptr = ptr->ai_next) {
        this->fd =
                socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (this->fd == -1){
            throw std::runtime_error("Error: File descriptor invalido");
        }

        s = connect(this->fd, ptr->ai_addr, ptr->ai_addrlen);
        if (s == -1){
            throw std::runtime_error("Error al conectarse al servidor");
        }
        connected = (s != -1);
    }
    freeaddrinfo(ai_list);
}


