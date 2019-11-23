#include "TurningRightState.h"
#include "../Car.h"

std::shared_ptr<CarTurningState> TurningRightState::handleInput(Car& car, const InputEnum& input){
    return CarTurningState::makeTurningState(input);
}

void TurningRightState::update(Car& car){
    //Turn right
    car.turnRight();
}
