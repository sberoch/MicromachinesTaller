#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include <Box2D/Box2D.h>
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class Car {
private:
    size_t id;
    b2Body* _carBody;
    int _health; //TODO health
    float _previous_x, _previous_y;

    void _setShapeAndFixture();
    void _changeSpeed(float new_linear_velocity);

public:
    Car(b2Body* carBody, size_t id);

    void start();
    void increaseSpeed(float to_increase);
    void decreaseSpeed(float to_decrease);

    void resetCar();

    const float x();
    const float y();
    const float speed();
    const b2Vec2 linearVelocity();

    ~Car();
};


#endif //MICROMACHINES_CAR_H
