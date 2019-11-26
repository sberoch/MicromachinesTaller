#include <iostream>
#include "Network/Server.h"

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Uso: mm_server <port>\n";
            return 1;
        }
        const char *portNumber = argv[1];
        Server server(portNumber);
        server.run();

    } catch(const std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Unexpected error\n";
    }

    return 0;
}