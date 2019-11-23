#include "WithoutAcceleratingState.h"
#include "Car.h"

std::shared_ptr<CarMovingState> WithoutAcceleratingState::handleInput(Car& car, const InputEnum& input){
    return CarMovingState::makeMovingState(input);
}

void WithoutAcceleratingState::update(Car& car) {}