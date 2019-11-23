#include "AcceleratingState.h"

#include "Car.h"

std::shared_ptr<CarMovingState> AcceleratingState::handleInput(Car& car, const InputEnum& input){
    return CarMovingState::makeMovingState(input);
}

void AcceleratingState::update(Car& car) {
    //Accelerate
    car.accelerate();
} 