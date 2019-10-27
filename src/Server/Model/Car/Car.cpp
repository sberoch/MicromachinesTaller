#include <src/Server/Model/Input.h>
#include <src/Server/Model/Car/Turning/NotTurningState.h>
#include "Car.h"

void Car::_setShapeAndFixture(){
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,2);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1; //Cuanta densidad?
    _carBody->CreateFixture(&boxFixtureDef);
}

Car::Car(b2Body* carBody) : _health(100), _previous_x(0), _previous_y(0), _maxSpeed(100), _maxForce(150),
                            _onTrack(true), _onGrass(false), _currentTraction(1){
    _carBody = carBody;
    _carBody->SetLinearVelocity( b2Vec2( 0, 0 ) ); //not moving
    _carBody->SetAngularVelocity( 0 );
    _setShapeAndFixture();

    _state = CarMovingState::makeMovingState(PRESS_NONE, PRESS_NONE);
    _turningState = new NotTurningState();

    _carBody->SetUserData(this);
}

void Car::resetCar(){
    _health = 100;
    //x should be middle, check if thereś already a car?
    b2Vec2 position = b2Vec2(0, _previous_y);
    _carBody->SetTransform(position, b2_pi/2); //See angle
}

void Car::accelerate(){
    //What to do with wake parameter?
    if (_carBody->GetLinearVelocity().x < _maxSpeed && _carBody->GetLinearVelocity().y < _maxSpeed)
        _carBody->ApplyForce(b2Vec2(0, 50 * _currentTraction), _carBody->GetWorldCenter(), true);
}

void Car::desaccelerate(){
    //What to do with wake parameter?
    _carBody->ApplyForce(b2Vec2(0, -50 * _currentTraction), _carBody->GetWorldCenter(), true);
}

void Car::turnLeft(){
    //_carBody->ApplyTorque(-10, true);
    _carBody->ApplyForce(b2Vec2(-50 * _currentTraction, 0), _carBody->GetWorldCenter(), true);
}

void Car::turnRight(){
    //_carBody->ApplyTorque(10, true);
    _carBody->ApplyForce(b2Vec2(50 * _currentTraction, 0), _carBody->GetWorldCenter(), true);
}

void Car::updateTraction(){
    if (_onTrack) {
        _currentTraction = 0.9f;
    } else if (_onGrass) {
        _currentTraction = 0.5f;
    }
}

void Car::startContact(){
    _onTrack = true;
}

void Car::endContact(){
    _onTrack = false;
}

void Car::handleInput(Input input){
    CarMovingState* state = _state->handleInput(*this, input);
    if (state != NULL){
        delete _state;
        _state = state;
    }
    CarTurningState* turningState = _turningState->handleInput(*this, input);
    if (turningState != NULL){
        delete _turningState;
        _turningState = turningState;
    }
}

void Car::update(){
    _state->update(*this);
    _turningState->update(*this);
    updateTraction();
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


class NegAcceleratingState : public CarMovingState {
public:
    CarMovingState* handleInput(Car& car, Input input){
        return makeMovingState(input, PRESS_DOWN);
    }

    void update(Car& car){
        car.desaccelerate();
    }
};

class AcceleratingState : public CarMovingState {
public:
    CarMovingState* handleInput(Car& car, Input input) {
        return makeMovingState(input, PRESS_UP);
    }

    void update(Car& car) {
        //Accelerate
        car.accelerate();
    }
};

class WithoutAcceleratingState : public CarMovingState {
public:
    CarMovingState* handleInput(Car& car, Input input) {
        return makeMovingState(input, PRESS_NONE);
    }

    void update(Car& car) {
        //Mover a vel constante
    }
};

CarMovingState* CarMovingState::makeMovingState(Input currentInput, Input prevInput){
    if (prevInput == PRESS_NONE && currentInput == PRESS_NONE){
        return new WithoutAcceleratingState();
    } else if (prevInput == PRESS_NONE && currentInput == PRESS_UP) {
        return new AcceleratingState();
    } else if(prevInput == PRESS_UP && currentInput == PRESS_DOWN) {
        return new NegAcceleratingState();
    } else if (prevInput == PRESS_DOWN && currentInput == PRESS_UP) {
        return new AcceleratingState();
    } else if (prevInput == PRESS_UP && currentInput == PRESS_NONE) {
        return new WithoutAcceleratingState();
    } else if (prevInput == PRESS_DOWN && currentInput == PRESS_NONE) {
        return new WithoutAcceleratingState();
    } else if (prevInput == PRESS_NONE && currentInput == PRESS_DOWN) {
        return new NegAcceleratingState();
    }

    return nullptr;
}
