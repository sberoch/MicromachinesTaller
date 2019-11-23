#ifndef MICROMACHINES_TURNINGLEFTSTATE_H
#define MICROMACHINES_TURNINGLEFTSTATE_H

#include "CarTurningState.h"

class TurningLeftState : public CarTurningState {
public:
    std::shared_ptr<CarTurningState> handleInput(Car& car, const InputEnum& input);

    void update(Car& car);
};

#endif //MICROMACHINES_TURNINGLEFTSTATE_H
