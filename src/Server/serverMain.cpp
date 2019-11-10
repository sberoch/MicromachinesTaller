#include <iostream>

#include "Model/Configuration.h"
#include "Model/GameThread.h"
#include "Network/Server.h"
#include <thread>

//int main(int argc, char const *argv[]) {
//    try {
////        std::shared_ptr<Configuration> configuration(
////                std::make_shared<Configuration>());
////        Game game(1, configuration);
////
////        game.run();
////        game.join();
//
//        Server server()
//    } catch (std::exception& e){
//        std::cout << e.what() << std::endl;
//    } catch (...) {
//        std::cout << "Server UnknownException.\n";
//    }
//
//	return 0;
//}

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