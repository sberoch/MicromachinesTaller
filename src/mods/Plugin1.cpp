#include <string>
#include <iostream>
#include "Plugin.h"

#define MAX_HEALTH 100
#define TO_DECREMENT_IF_HALF_HEALTH 5
#define TO_DECREMENT_IF_MORE_THAN_HALF 10

//Plugin to decrement speed in damaged cars.
class Plugin1 : public Plugin {
public:
    void run(WorldDTO* world){
        for (size_t i=0; i<world->cars_size; ++i){
            if (world->cars[i].health < MAX_HEALTH/2 &&
               (world->cars[i].maxForwardDrive - TO_DECREMENT_IF_HALF_HEALTH) > 0) {
                world->cars[i].maxForwardDrive -= TO_DECREMENT_IF_HALF_HEALTH;
            } else if (world->cars[i].health < MAX_HEALTH - 20 &&
                      (world->cars[i].maxForwardDrive - TO_DECREMENT_IF_MORE_THAN_HALF) > 0) {
                world->cars[i].maxForwardDrive -= TO_DECREMENT_IF_MORE_THAN_HALF;
            }
        }
    }

    ~Plugin1() = default;
};

extern "C" Plugin* factory(void) {
    return static_cast<Plugin*>(new Plugin1);
}

