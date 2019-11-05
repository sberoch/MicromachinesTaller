#ifndef MICROMACHINES_CARMOVINGSTATE_H
#define MICROMACHINES_CARMOVINGSTATE_H

#include "../../../Common/Event/CommandEvent.h"

class Car;
class WithoutAcceleratingState;
class AcceleratingState;
class NegAcceleratingState;

class CarMovingState {
public:
    static CarMovingState* makeMovingState(const InputEnum& input);
    virtual CarMovingState* handleInput(Car& car, const InputEnum& input) = 0;
    virtual void update(Car& car) = 0;
    virtual ~CarMovingState(){}
};

#endif //MICROMACHINES_CARMOVINGSTATE_H
