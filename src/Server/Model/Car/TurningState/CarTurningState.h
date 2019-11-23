#ifndef MICROMACHINES_CARTURNINGSTATE_H
#define MICROMACHINES_CARTURNINGSTATE_H

#include "../../../../Common/Event/CommandEvent.h"

class Car;
class TurningRightState;
class TurningLeftState;
class NotTurningState;

class CarTurningState {
public:
    static std::shared_ptr<CarTurningState> makeTurningState(const InputEnum& input);
    virtual std::shared_ptr<CarTurningState> handleInput(Car& car, const InputEnum& input) = 0;
    virtual void update(Car& car) = 0;
    virtual ~CarTurningState(){}
};

#endif //MICROMACHINES_CARTURNINGSTATE_H
