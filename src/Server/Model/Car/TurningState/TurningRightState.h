#ifndef MICROMACHINES_TURNINGRIGHTSTATE_H
#define MICROMACHINES_TURNINGRIGHTSTATE_H

#include "CarTurningState.h"

class TurningRightState : public CarTurningState {
public:
    std::shared_ptr<CarTurningState> handleInput(Car& car, const InputEnum& input);
    void update(Car& car);
};

#endif //MICROMACHINES_TURNINGRIGHTSTATE_H
