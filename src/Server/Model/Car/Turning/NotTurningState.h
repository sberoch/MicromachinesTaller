#ifndef MICROMACHINES_NOTTURNINGSTATE_H
#define MICROMACHINES_NOTTURNINGSTATE_H

#include "src/Server/Model/Car/Turning/CarTurningState.h"

#include "TurningRightState.h"
#include "TurningLeftState.h"

class NotTurningState : public CarTurningState{
public:
    virtual CarTurningState* handleInput(Car& car, Input input){
        if (input == PRESS_LEFT) {
            return new TurningLeftState();
        } else if (input == PRESS_RIGHT) {
            return new TurningRightState();
        }
        return nullptr;
    }

    virtual void update(Car& car){
        //Continue in straight direction
    }
};

#endif //MICROMACHINES_NOTTURNINGSTATE_H
