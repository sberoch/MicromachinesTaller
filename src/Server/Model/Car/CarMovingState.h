#ifndef MICROMACHINES_CARMOVINGSTATE_H
#define MICROMACHINES_CARMOVINGSTATE_H

#include "../Input.h"

class Car;

class CarMovingState{
public:
    virtual CarMovingState* handleInput(Car& car, Input input){}
    virtual void update(Car& car){}
    virtual ~CarMovingState(){}
};

#endif //MICROMACHINES_CARMOVINGSTATE_H
