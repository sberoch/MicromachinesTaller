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
    float _maxSpeed;
    float _maxForce;

    size_t id;
    b2Body* _carBody;
    CarMovingState* _state;
    CarTurningState* _turningState;

    int _health;
    float _previous_x, _previous_y;

    bool _onTrack;
    bool _onGrass;
    float _currentTraction;

    void _setShapeAndFixture();

public:
    Car(b2Body* carBody);

    void accelerate();
    void desaccelerate();
    void turnLeft();
    void turnRight();

    //Contact with floor
    void startContact();
    void endContact();
    void updateTraction();

    void resetCar();

    virtual void handleInput(Input input);
    virtual void update();

    const float x();
    const float y();
    const float speed();

    ~Car();
};

class CarMovingState{
public:
    static CarMovingState* makeMovingState(Input currentInput, Input prevInput);
    virtual CarMovingState* handleInput(Car& car, Input input) = 0;
    virtual void update(Car& car) = 0;
    virtual ~CarMovingState(){}
};






#endif //MICROMACHINES_CAR_H
