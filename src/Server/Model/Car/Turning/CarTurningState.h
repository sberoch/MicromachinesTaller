#ifndef MICROMACHINES_CARTURNINGSTATE_H
#define MICROMACHINES_CARTURNINGSTATE_H

#include "src/Server/Model/Input.h"
class Car;

class CarTurningState {
public:
    virtual CarTurningState* handleInput(Car& car, Input input){}
    virtual void update(Car& car){}
    virtual ~CarTurningState(){}
};

#endif //MICROMACHINES_CARTURNINGSTATE_H
