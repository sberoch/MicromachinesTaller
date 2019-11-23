#ifndef MICROMACHINES_NOTTURNINGSTATE_H
#define MICROMACHINES_NOTTURNINGSTATE_H

#include "CarTurningState.h"

class NotTurningState : public CarTurningState{
public:
    std::shared_ptr<CarTurningState> handleInput(Car& car, const InputEnum& input);

    void update(Car& car);
};



#endif //MICROMACHINES_NOTTURNINGSTATE_H
