#include <iostream>


#include "Model/GameThread.h"
#include "Network/Server.h"


int main(int argc, char *argv[]) {
    try {
        const char *portNumber = "8888";

//        if (argv[PORT_NUMBER_POSITION] != nullptr)
//            portNumber = argv[PORT_NUMBER_POSITION];

        Server server(portNumber);
        server.run();

    } catch(const std::exception &e) {
        printf("ERROR: %s", e.what());
    } catch(...) {
        printf("Unknown error from main.");
    }

    return 0;
}




//int main(int argc, char *argv[]) {
//    std::unordered_map<int, int*> map;
//    std::atomic_bool running(false);
//    int n1 = 1;
//    int n2 = 2;
//    int* nulo = nullptr;
//    int* v1 = &n1;
//    int* v2 = &n2;
//
//    map.insert({n1, v1});
//    map.insert({n2, v2});
//    map.insert({3, nulo});
//
//    eraseNulls(map);
//
//    std::cout << "Hola " << std::endl;
//
//    return 0;
//}