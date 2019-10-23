#ifndef MICROMACHINES_TURNINGRIGHTSTATE_H
#define MICROMACHINES_TURNINGRIGHTSTATE_H

#include "CarTurningState.h"
#include "NotTurningState.h"

class TurningRightState : public CarTurningState {
public:
    virtual CarTurningState* handleInput(Car& car, Input input){
        if (input == PRESS_LEFT) {
            return new TurnLeftState();
        } else if (input == RELEASE_RIGHT) {
            return new NotTurningState();
        }
        return nullptr;
    }

    virtual void update(Car& car){
        //Turn right
    }
};

#endif //MICROMACHINES_TURNINGRIGHTSTATE_H
