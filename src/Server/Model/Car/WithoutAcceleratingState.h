#ifndef MICROMACHINES_WITHOUTACCELERATINGSTATE_H
#define MICROMACHINES_WITHOUTACCELERATINGSTATE_H

#include "../Input.h"
#include "CarMovingState.h"
#include "AcceleratingState.h"

class WithoutAcceleratingState : public CarMovingState {
public:
    virtual CarMovingState* handleInput(Car& car, Input input) {
        if (input == PRESS_UP){
            return new AcceleratingState();
        } else if (input == PRESS_DOWN) {
            return new NegAcceleratingState();
        }
        return nullptr;
    }

    virtual void update(Car& car) {
        //Mover a vel constante
    }
};

#endif //MICROMACHINES_WITHOUTACCELERATINGSTATE_H
