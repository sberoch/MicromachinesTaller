#ifndef MICROMACHINES_ACCELERATINGSTATE_H
#define MICROMACHINES_ACCELERATINGSTATE_H

#include "CarState.h"
#include "../Input.h"
#include "NegAcceleratingState.h"

class AcceleratingState : public CarState {
public:
    virtual CarState* handleInput(Car& car, Input input) {
        if (input == PRESS_DOWN){
           return new NegAcceleratingState();
        }
        return nullptr;
    }

    virtual void update(Car& car) {
        //Accelerate
        car.accelerate();
    }
};

#endif //MICROMACHINES_ACCELERATINGSTATE_H
