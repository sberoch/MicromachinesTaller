#ifndef MICROMACHINES_TURNINGLEFTSTATE_H
#define MICROMACHINES_TURNINGLEFTSTATE_H

#include "src/Server/Model/Car/Turning/CarTurningState.h"
#include "TurningRightState.h"

class TurningLeftState : public CarTurningState {
public:
    virtual CarTurningState* handleInput(Car& car, Input input){
        if (input == PRESS_RIGHT) {
            return new TurningRightState();
        } else if (input == RELEASE_LEFT) {
            return new NotTurningState();
        }
        return nullptr;
    }

    virtual void update(Car& car){
        //Turn left
        car.turnLeft();
    }
};

#endif //MICROMACHINES_TURNINGLEFTSTATE_H
