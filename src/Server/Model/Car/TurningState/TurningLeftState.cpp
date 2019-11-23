#include "TurningLeftState.h"
#include "../Car.h"

std::shared_ptr<CarTurningState> TurningLeftState::handleInput(Car& car, const InputEnum& input){
    return makeTurningState(input);
}

void TurningLeftState::update(Car& car){
    //Turn left
    car.turnLeft();
}