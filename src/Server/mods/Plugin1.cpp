#include <string>
#include <iostream>
#include "Plugin.h"

//Plugin to create random modifiers
class Plugin1 : public Plugin {
public:
    std::string message(void) {
        return "Hello. I'm Test Widget1\n";
    }

    void run(WorldDTO* world){
        for (size_t i=0; i<world->cars_size; ++i){
            std::cout << "id " << world->cars[i]->id << '\n';
            std::cout << "pos " << world->cars[i]->x << " " << world->cars[i]->y << '\n';
        }
    }
};

extern "C" Plugin* factory(void) {
    return static_cast<Plugin*>(new Plugin1);
}