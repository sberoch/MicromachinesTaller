#ifndef MICROMACHINES_NEGACCELERATINGSTATE_H
#define MICROMACHINES_NEGACCELERATINGSTATE_H

#include <src/Server/Model/Input.h>
#include "CarState.h"
#include "AcceleratingState.h"
#include "WithoutAcceleratingState.h"

class NegAcceleratingState : public CarState {
    virtual CarState* handleInput(Car& car, Input input){
        /*if (input == PRESS_UP) {
            return new AcceleratingState();
        } else if (input == PRESS_NONE) {
            return new WithoutAcceleratingState();
        }*/
        return nullptr;
    }

    virtual void update(Car& car){
        car.desaccelerate();
    }
};

#endif //MICROMACHINES_NEGACCELERATINGSTATE_H
