#include <set>
#include <sstream>
#include "File.h"
#include "../Common/Socket.h"
#include "AcceptingThread.h"
#include "../Common/ServerSnapshot.h"

#define Q_MINUSCULA 'q'
#define PORT_NUMBER_POSITION 1



int main(int argc, char *argv[]) {
    try {
        const char *portNumber = "8021";

//        if (argv[PORT_NUMBER_POSITION] != nullptr)
//            portNumber = argv[PORT_NUMBER_POSITION];

        Socket acceptSocket = Socket::createAcceptingSocket(portNumber);

        AcceptingThread acceptor(acceptSocket);
        acceptor.start();

        char c = (char) getchar();

        if (c == Q_MINUSCULA){
            acceptSocket.stop();
        }

        acceptor.join();
    } catch(const std::exception &e) {
        printf("ERROR: %s", e.what());
    } catch(...) {
        printf("Unknown error from main.");
    }

    return 0;
}
