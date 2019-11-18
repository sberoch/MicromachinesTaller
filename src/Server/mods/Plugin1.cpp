#include <string>
#include <iostream>
#include "Plugin.h"

class Plugin1 : public Plugin {
public:
    std::string message(void) {
        return "Hello. I'm Test Widget1\nOh and the unique_signal is: " + std::to_string(unique_signal);
    }
};

extern "C" Plugin* factory(void) {
    return static_cast<Plugin*>(new Plugin1);
}