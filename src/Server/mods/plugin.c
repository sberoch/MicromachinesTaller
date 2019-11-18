#include "plugin.h"
#include "DTOs.h"

#define MAX_HEALTH 100
#define TO_DECREMENT_IF_HALF_HEALTH 30
#define TO_DECREMENT_IF_MORE_THAN_HALF 10

int plugin_func(void) {
    printf("Hello from the plugin!\n");
    return 42;
}

void plugin_car_damaged(CarDTO_t* cars[], size_t size){
    for (size_t i=0; i<size; ++i){
        if (cars[i]->health < MAX_HEALTH/2) {
            cars[i]->maxForwardSpeed -= TO_DECREMENT_IF_HALF_HEALTH;
        } else if (cars[i]->health < MAX_HEALTH) {
            cars[i]->maxForwardSpeed -= TO_DECREMENT_IF_MORE_THAN_HALF;
        }
    }
}