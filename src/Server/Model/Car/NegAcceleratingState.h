#ifndef MICROMACHINES_NEGACCELERATINGSTATE_H
#define MICROMACHINES_NEGACCELERATINGSTATE_H

#include "../Input.h"
#include "CarMovingState.h"
#include "AcceleratingState.h"

class NegAcceleratingState : public CarMovingState {
public:
    virtual CarMovingState* handleInput(Car& car, Input input){
        if (input == PRESS_UP) {
            //return new AcceleratingState();
        } else if (input == PRESS_NONE) {
            //return new WithoutAcceleratingState();
        }
        return nullptr;
    }

    virtual void update(Car& car){
        car.desaccelerate();
    }
};

#endif //MICROMACHINES_NEGACCELERATINGSTATE_H
