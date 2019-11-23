#include "CarTurningState.h"

#include "TurningRightState.h"
#include "TurningLeftState.h"
#include "NotTurningState.h"

std::shared_ptr<CarTurningState> CarTurningState::makeTurningState(const InputEnum& input){
    if (input == STOP_TURNING_LEFT || input == STOP_TURNING_RIGHT) {
        return std::shared_ptr<CarTurningState>(new NotTurningState());
    } else if (input == TURN_RIGHT) {
        return std::shared_ptr<CarTurningState>(new TurningRightState());
    } else if(input == TURN_LEFT) {
        return std::shared_ptr<CarTurningState>(new TurningLeftState());
    }

    return nullptr;
}

