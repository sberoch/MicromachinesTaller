#include "NegAcceleratingState.h"

CarMovingState* NegAcceleratingState::handleInput(Car& car, const InputEnum& input){
    return makeMovingState(input);
}

void NegAcceleratingState::update(Car& car){
    car.desaccelerate();
}
