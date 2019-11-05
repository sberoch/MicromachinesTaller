#include "AcceleratingState.h"

CarMovingState* AcceleratingState::handleInput(Car& car, const InputEnum& input){
    return makeMovingState(input);
}

void AcceleratingState::update(Car& car) {
    //Accelerate
    car.accelerate();
}