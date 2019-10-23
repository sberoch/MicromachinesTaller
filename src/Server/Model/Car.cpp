#include "Car.h"

void Car::_setShapeAndFixture(){
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,2);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1; //Cuanta densidad?
    _carBody->CreateFixture(&boxFixtureDef);
}

Car::Car(b2Body* carBody, size_t id) : _health(100), _previous_x(0), _previous_y(0) {
    _carBody = carBody;
    _carBody->SetLinearVelocity( b2Vec2( 0, 0 ) ); //not moving
    _carBody->SetAngularVelocity( 0 );
    _setShapeAndFixture();
}



void Car::start(){
    b2Vec2 linear_velocity = b2Vec2(0, 5);
    _carBody->SetLinearVelocity(linear_velocity);
}

void Car::_changeSpeed(float new_linear_velocity){
    b2Vec2 linear_velocity = b2Vec2(0, new_linear_velocity);
    _carBody->SetLinearVelocity(linear_velocity);
}

void Car::increaseSpeed(float to_increase){
    float new_y_vel = _carBody->GetLinearVelocity().y + to_increase;
    _changeSpeed(new_y_vel);
}

void Car::decreaseSpeed(float to_decrease){
    float new_y_vel = _carBody->GetLinearVelocity().y - to_decrease;
    _changeSpeed(new_y_vel);
}

void Car::resetCar(){
    _health = 100;
    //x should be middle, check if thereś already a car?
    b2Vec2 position = b2Vec2(0, _previous_y);
    _carBody->SetTransform(position, b2_pi/2); //See angle
}

const float Car::x(){
    return _carBody->GetPosition().x;
}

const float Car::y(){
    return _carBody->GetPosition().y;
}

const b2Vec2 Car::linearVelocity(){
    return _carBody->GetLinearVelocity();
}

const float Car::speed(){
    b2Vec2 linearVelocity = _carBody->GetLinearVelocity();
    return linearVelocity.y;
}

Car::~Car(){}
