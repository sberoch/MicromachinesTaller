#include "CarMovingState.h"

#include "WithoutAcceleratingState.h"
#include "AcceleratingState.h"
#include "NegAcceleratingState.h"

CarMovingState* CarMovingState::makeMovingState(const InputEnum& input){
    if (input == STOP_ACCELERATING || input == STOP_DESACCELERATING){
        return new WithoutAcceleratingState();
    } else if (input == ACCELERATE) {
        return new AcceleratingState();
    } else if(input == DESACCELERATE) {
        return new NegAcceleratingState();
    }
    return nullptr;
}
