#ifndef MICROMACHINES_ACCELERATINGSTATE_H
#define MICROMACHINES_ACCELERATINGSTATE_H

#include "CarMovingState.h"
#include "../Input.h"
#include "NegAcceleratingState.h"

class AcceleratingState : public CarMovingState {
public:
    virtual CarMovingState* handleInput(Car& car, Input input) {
        if (input == PRESS_DOWN){
           return new NegAcceleratingState();
        } else if (input == PRESS_NONE) {
            //return new WithoutAcceleratingState();
        }
        return nullptr;
    }

    virtual void update(Car& car) {
        //Accelerate
        car.accelerate();
    }
};

#endif //MICROMACHINES_ACCELERATINGSTATE_H
