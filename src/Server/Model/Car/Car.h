#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include "../../../../Box2D/Box2D.h"

#include "../Input.h"

class CarTurningState;
class CarMovingState;

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class Car {
private:
    float _max_speed;
    size_t id;
    b2Body* _carBody;
    CarMovingState* _state;
    CarTurningState* _turningState;

    int _health;
    float _previous_x, _previous_y;

    void _setShapeAndFixture();

public:
    Car(b2Body* carBody);

    void accelerate();
    void desaccelerate();
    void turnLeft();
    void turnRight();

    void resetCar();

    virtual void handleInput(Input input);
    virtual void update();

    const float x();
    const float y();
    const float speed();

    ~Car();
};


#endif //MICROMACHINES_CAR_H
