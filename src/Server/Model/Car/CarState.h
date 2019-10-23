#ifndef MICROMACHINES_CARSTATE_H
#define MICROMACHINES_CARSTATE_H

#include "../Input.h"

class Car;

class CarState{
public:
    virtual CarState* handleInput(Car& car, Input input){}
    virtual void update(Car& car){}
    virtual ~CarState(){}
};

#endif //MICROMACHINES_CARSTATE_H
