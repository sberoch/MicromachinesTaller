#include <set>
#include <sstream>
#include <utility>
#include "../../Common/Socket.h"
#include "AcceptingThread.h"
#include "../../Common/ServerSnapshot.h"
#include "Server.h"

//#define Q_MINUSCULA 'q'
//#define PORT_NUMBER_POSITION 1
//
//
//
//int main(int argc, char *argv[]) {
//    try {
//        const char *portNumber = "8888";
//
////        if (argv[PORT_NUMBER_POSITION] != nullptr)
////            portNumber = argv[PORT_NUMBER_POSITION];
//
//        Server server(portNumber);
//        server.run();
//
//    } catch(const std::exception &e) {
//        printf("ERROR: %s", e.what());
//    } catch(...) {
//        printf("Unknown error from main.");
//    }
//
//    return 0;
//}

