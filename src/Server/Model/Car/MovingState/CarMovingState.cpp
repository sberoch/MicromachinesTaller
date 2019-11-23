#include "CarMovingState.h"

#include "WithoutAcceleratingState.h"
#include "AcceleratingState.h"
#include "NegAcceleratingState.h"

std::shared_ptr<CarMovingState> CarMovingState::makeMovingState(const InputEnum& input){
    if (input == STOP_ACCELERATING || input == STOP_DESACCELERATING){
        return std::shared_ptr<CarMovingState>(new WithoutAcceleratingState());
    } else if (input == ACCELERATE) {
        return std::shared_ptr<CarMovingState>(new AcceleratingState());
    } else if(input == DESACCELERATE) {
        return std::shared_ptr<CarMovingState>(new NegAcceleratingState());
    }
    return nullptr;
}