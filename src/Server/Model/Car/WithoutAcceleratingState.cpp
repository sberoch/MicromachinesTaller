#include "WithoutAcceleratingState.h"

CarMovingState* WithoutAcceleratingState::handleInput(Car& car, const InputEnum& input){
    return makeMovingState(input);
}

void WithoutAcceleratingState::update(Car& car) {
    //Rozamiento con el piso???
    //car.friction();
}