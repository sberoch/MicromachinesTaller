#include <set>
#include <sstream>
#include <utility>
#include "../Common/Socket.h"
#include "AcceptingThread.h"
#include "../Common/ServerSnapshot.h"
#include "Server.h"

<<<<<<< Updated upstream
#define Q_MINUSCULA 'q'
#define PORT_NUMBER_POSITION 1



//int main(int argc, char *argv[]) {
//    try {
//        const char *portNumber = "8888";
//
////        if (argv[PORT_NUMBER_POSITION] != nullptr)
////            portNumber = argv[PORT_NUMBER_POSITION];
//
//        Server server(portNumber);
//
//    } catch(const std::exception &e) {
//        printf("ERROR: %s", e.what());
//    } catch(...) {
//        printf("Unknown error from main.");
//    }
//
//    return 0;
//}

#include "../Common/json.hpp"

using json = nlohmann::json;

class Test{
public:
    int n1;
    std::string s1;
    Test(): n1(0), s1(" "){}
    Test(int n1, std::string s1): n1(n1), s1(std::move(s1)){}
};

int main(int argc, char *argv[]) {
    Test t1(1, "Hola");
    Test t2(2, "Chau");

    std::vector<Test> vec;
    vec.push_back(t1);
    vec.push_back(t2);

    json j1;
    j1["n1"] = t1.n1;
    j1["s1"] = t1.s1;

    json j2;
    j2["n1"] = t2.n1;
    j2["s1"] = t2.s1;

    json jVec;
    jVec.push_back(j1);
    jVec.push_back(j2);


    std::string s1 = jVec.dump();


    Test t3;
    Test t4;
    auto j3 = json::parse(s1);
    std::vector<Test> vector;

    for (auto& element : j3) {
        Test actualTest(element["n1"], element["s1"]);
        vector.push_back(actualTest);
    }

    std::vector<Test> otroVector;
}
=======
#include "Model/Configuration.h"
#include "Model/Game.h"
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
>>>>>>> Stashed changes
