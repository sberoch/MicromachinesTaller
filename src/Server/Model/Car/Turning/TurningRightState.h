#ifndef MICROMACHINES_TURNINGRIGHTSTATE_H
#define MICROMACHINES_TURNINGRIGHTSTATE_H

#include "CarTurningState.h"
#include "NotTurningState.h"
#include "src/Server/Model/Car/Car.h"

class TurningRightState : public CarTurningState {
public:
    virtual CarTurningState* handleInput(Car& car, Input input){
        if (input == PRESS_LEFT) {
            //return new TurnLeftState();
            return nullptr;
        } else if (input == RELEASE_RIGHT) {
            //return new NotTurningState();
            return nullptr;
        }
        return nullptr;
    }

    virtual void update(Car& car){
        //Turn right
        car.turnRight();
    }
};

#endif //MICROMACHINES_TURNINGRIGHTSTATE_H
