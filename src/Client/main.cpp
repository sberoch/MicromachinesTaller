#include "SceneSelector.h"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
	try {
		const std::string hostName = "localhost";//std::string(argv[1]);
        const std::string portNumber = "8888";//std::string(argv[2]);

		SceneSelector sceneSelector(1000, 800, hostName, portNumber);
		sceneSelector.run();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Unexpected error\n";
	}
	return 0;
}
