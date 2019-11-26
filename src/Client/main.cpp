#include "SceneSelector.h"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
	try {
		if (argc != 5) {
			std::cerr << "Uso: mm_client <hostname> <port> <window width> <window height>\n";
			return 1;
		}
		const std::string hostName = std::string(argv[1]);
        const std::string portNumber = std::string(argv[2]);

        int wScreen = atoi(argv[3]);
        int hScreen = atoi(argv[4]);

		SceneSelector sceneSelector(wScreen, hScreen, hostName, portNumber);
		sceneSelector.run();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Unexpected error\n";
	}
	return 0;
}
