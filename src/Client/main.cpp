#include "SceneSelector.h"
#include <iostream>

int main(int argc, char const *argv[]) {
	try {
		SceneSelector sceneSelector(1000, 800);
		sceneSelector.run();
	} catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Unexpected error\n";
	}
	return 0;
}
