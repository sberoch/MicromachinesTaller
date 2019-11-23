#ifndef MICROMACHINES_NEGACCELERATINGSTATE_H
#define MICROMACHINES_NEGACCELERATINGSTATE_H

#include "CarMovingState.h"

class NegAcceleratingState : public CarMovingState {
    std::shared_ptr<CarMovingState> handleInput(Car& car, const InputEnum& input);
    void update(Car& car);
};


#endif //MICROMACHINES_NEGACCELERATINGSTATE_H