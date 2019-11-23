#ifndef MICROMACHINES_CARMOVINGSTATE_H
#define MICROMACHINES_CARMOVINGSTATE_H

#include "../../../Common/Event/CommandEvent.h"

class Car;
class WithoutAcceleratingState;
class AcceleratingState;
class NegAcceleratingState;

class CarMovingState{
public:
    static std::shared_ptr<CarMovingState> makeMovingState(const InputEnum& input);
    virtual std::shared_ptr<CarMovingState> handleInput(Car& car, const InputEnum& input) = 0;
    virtual void update(Car& car) = 0;
    virtual ~CarMovingState(){}
};

#endif //MICROMACHINES_CARMOVINGSTATE_H