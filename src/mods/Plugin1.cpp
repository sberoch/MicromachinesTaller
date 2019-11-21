#include <string>
#include <iostream>
#include "Plugin.h"

#define MAX_HEALTH 100
#define TO_DECREMENT_IF_HALF_HEALTH 30
#define TO_DECREMENT_IF_MORE_THAN_HALF 10

//Plugin to decrement speed in damaged cars.
class Plugin1 : public Plugin {
public:
    std::string message(void) {
        return "Hello. I'm Test Widget1\n";
    }

    void run(WorldDTO* world){
        for (size_t i=0; i<world->cars_size; ++i){
            if (world->cars[i].health < MAX_HEALTH/2) {
                std::cout << "\nhealt menor a 50\n";
                world->cars[i].maxForwardSpeed -= TO_DECREMENT_IF_HALF_HEALTH;
            } else if (world->cars[i].health < MAX_HEALTH - 20) {
                std::cout << "\nhealth menor a 80\n";
                world->cars[i].maxForwardSpeed -= TO_DECREMENT_IF_MORE_THAN_HALF;
            }
        }
    }
};

extern "C" Plugin* factory(void) {
    return static_cast<Plugin*>(new Plugin1);
}

