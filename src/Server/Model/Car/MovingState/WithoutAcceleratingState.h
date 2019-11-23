#ifndef MICROMACHINES_WITHOUTACCELERATINGSTATE_H
#define MICROMACHINES_WITHOUTACCELERATINGSTATE_H

#include "CarMovingState.h"

class WithoutAcceleratingState : public CarMovingState {
public:
    std::shared_ptr<CarMovingState> handleInput(Car& car, const InputEnum& input);
    void update(Car& car);
};

#endif //MICROMACHINES_WITHOUTACCELERATINGSTATE_H