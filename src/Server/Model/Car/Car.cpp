#include <src/Server/Model/Input.h>
#include "Car.h"
#include "WithoutAcceleratingState.h"

void Car::_setShapeAndFixture(){
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,2);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1; //Cuanta densidad?
    _carBody->CreateFixture(&boxFixtureDef);
}

Car::Car(b2Body* carBody) : _health(100), _previous_x(0), _previous_y(0) {
    _carBody = carBody;
    _carBody->SetLinearVelocity( b2Vec2( 0, 0 ) ); //not moving
    _carBody->SetAngularVelocity( 0 );
    _setShapeAndFixture();

    _state = new WithoutAcceleratingState;
}

void Car::resetCar(){
    _health = 100;
    //x should be middle, check if thereś already a car?
    b2Vec2 position = b2Vec2(0, _previous_y);
    _carBody->SetTransform(position, b2_pi/2); //See angle
}

void Car::accelerate(){
    //What to do with wake parameter?
    _carBody->ApplyForce(b2Vec2(0, 50), _carBody->GetWorldCenter(), true);
}

void Car::desaccelerate(){
    //What to do with wake parameter?
    _carBody->ApplyForce(b2Vec2(0, -50), _carBody->GetWorldCenter(), true);
}

void Car::handleInput(Input input){
    CarState* state = _state->handleInput(*this, input);
    if (state != NULL){
        delete _state;
        _state = state;
    }
}

void Car::update(){
    _state->update(*this);
}

const float Car::x(){
    return _carBody->GetPosition().x;
}

const float Car::y(){
    return _carBody->GetPosition().y;
}

const float Car::speed(){
    b2Vec2 linearVelocity = _carBody->GetLinearVelocity();
    return linearVelocity.y;
}

Car::~Car(){
    delete _state;
}
