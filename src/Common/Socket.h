//
// Created by alvaro on 27/9/19.
//

#ifndef HONEYPOT_COMMONSOCKET_H
#define HONEYPOT_COMMONSOCKET_H

#include <string>

class Socket {
private:
    int fd;

    //Setea los hints para el servidor
    static void setHintsForServer(void *addrinfo);

    //Crea un socket a partir de un file descriptor.
    explicit Socket(int fd);

public:
    //Crea un socket con un fd por defecto. En donde el dominio es IPV4 y
    //la conexion es TCP.
    Socket();

    //Mueve el socket, dejandolo invalido.
    Socket(Socket &&other) noexcept;

    //Marca el socket como pasivo. Para el backlog, maximo numero de conexiones
    //pendientes en la cola, se usa SOMAXCONN.
    void listen();

    //Acepta al cliente y devuelve el socket.
    Socket accept();

    //Loop hasta enviar el mensaje con longitud messageLength.
    void send(char *buffer, int messageLength);

    //Loop hasta recibir el mensaje de longitud length.
    void receive(char *buffer, int length);

    //Ejecuta las operaciones, dejando al servidor listo para realizar el
    // loop aceptador.
    void setServerReady(const char *portNumber);

    //Shutdown y close forzado.
    void stop();

    //Utilizado por el cliente para conectarse al servidor.
    void connectToServer(const std::string &hostName,
                        const std::string &portNumber);

    //Shutdown y close.
    ~Socket();
};



#endif //HONEYPOT_COMMONSOCKET_H
