#include "NegAcceleratingState.h"
#include "../Car.h"

std::shared_ptr<CarMovingState> NegAcceleratingState::handleInput(Car& car, const InputEnum& input){
    return CarMovingState::makeMovingState(input);
}

void NegAcceleratingState::update(Car& car){
    car.desaccelerate();
}