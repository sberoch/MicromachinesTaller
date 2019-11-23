#include "NotTurningState.h"
#include "../Car.h"

std::shared_ptr<CarTurningState> NotTurningState::handleInput(Car& car, const InputEnum& input){
    return makeTurningState(input);
}

void NotTurningState::update(Car& car){}
