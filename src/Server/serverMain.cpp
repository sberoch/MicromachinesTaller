#include <iostream>

#include "Model/Configuration.h"
#include "Model/GameThread.h"
#include <thread>

extern "C" {
#include "mods/plugin.h"
}

int main(int argc, char const *argv[]) {
    try {
        std::shared_ptr<Configuration> configuration(std::make_shared<Configuration>());
        //Use move
        GameThread game(1, configuration);

        game.run();
        game.join();
    } catch (...) {
        std::cout << "Server UnknownException.\n";
    }

	return 0;
}