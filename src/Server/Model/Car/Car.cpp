#include <src/Server/Model/Input.h>
#include "Car.h"

void Car::_setShapeAndFixture(){
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,2);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1; //Cuanta densidad?
    _carBody->CreateFixture(&boxFixtureDef);
}

Car::Car(b2Body* carBody) : _health(100), _previous_x(0), _previous_y(0), _maxForwardSpeed(100),
                            _maxBackwardSpeed(-20), _maxForce(150), _isMoving(false),
                            _onTrack(true), _onGrass(false), _currentTraction(1), _carBody(carBody){
    _carBody->SetLinearVelocity( b2Vec2( 0, 0 ) ); //not moving
    _carBody->SetAngularVelocity( 0 );
    _setShapeAndFixture();

    _state = CarMovingState::makeMovingState(PRESS_NONE, PRESS_NONE);
    _turningState = CarTurningState::makeTurningState(PRESS_NONE, PRESS_NONE);

    _carBody->SetUserData(this);
}

void Car::resetCar(){
    _health = 100;
    //x should be middle, check if thereś already a car?
    b2Vec2 position = b2Vec2(0, _previous_y);
    _carBody->SetTransform(position, b2_pi/2); //See angle
}

b2Vec2 Car::getLateralVelocity(){
    b2Vec2 currentRightNormal = _carBody->GetWorldVector(b2Vec2(1, 0));
    return b2Dot(currentRightNormal, _carBody->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 Car::getForwardVelocity(){
    b2Vec2 currentForwardNormal = _carBody->GetWorldVector(b2Vec2(0,1));
    return b2Dot(currentForwardNormal, _carBody->GetLinearVelocity()) * currentForwardNormal;
}

void Car::accelerate(){
    //float velocityChange = _maxForwardSpeed - currentSpeed;
    //float force = _carBody->GetMass() * velocityChange / (1/30.0);
    //_carBody->ApplyForce(b2Vec2(0, force), _carBody->GetWorldCenter(), true);
    _isMoving = true;
    b2Vec2 currentSpeed = _carBody->GetLinearVelocity();
    float velocityChange = _maxForwardSpeed - currentSpeed.y;
    float impulse = _carBody->GetMass() * velocityChange;
    if (currentSpeed.y < _maxForwardSpeed)
        _carBody->ApplyLinearImpulse(b2Vec2(0, 10), _carBody->GetWorldCenter(), true);
}

void Car::desaccelerate(){
    //b2Vec2 currentForwardNormal = _carBody->GetWorldVector( b2Vec2(0,1) );
    //float currentSpeed = b2Dot( getForwardVelocity(), currentForwardNormal );

    //float velocityChange = abs(_maxBackwardSpeed - currentSpeed);
    //float force = _carBody->GetMass() * velocityChange / (1/30.0);
    //_carBody->ApplyForce(b2Vec2(0, -force), _carBody->GetWorldCenter(), true);

    //float velocityChange = _maxBackwardSpeed - currentSpeed;
    //float impulse = _carBody->GetMass() * velocityChange;
    //_carBody->ApplyLinearImpulse(b2Vec2(0, impulse), _carBody->GetWorldCenter(), true);
    _isMoving = true;
    b2Vec2 currentSpeed = _carBody->GetLinearVelocity();
    float velocityChange = _maxBackwardSpeed - currentSpeed.y;
    float impulse = _carBody->GetMass() * velocityChange;
    if (_maxBackwardSpeed < currentSpeed.y)
        _carBody->ApplyLinearImpulse(b2Vec2(0, -10), _carBody->GetWorldCenter(), true);
}

void Car::friction(){
    float currentSpeed = _carBody->GetLinearVelocity().y;

    //float velocityChange = _currentTraction * speed();
    //float force = _carBody->GetMass() * velocityChange / (1/30.0);
    //_carBody->ApplyForce(b2Vec2(0, force), _carBody->GetWorldCenter(), true);

    float velocityChange = -currentSpeed;
    //float impulse = _currentTraction * _carBody->GetMass() * velocityChange;
    if (currentSpeed > 0)
        _carBody->ApplyLinearImpulse(b2Vec2(0, -10 * _currentTraction), _carBody->GetWorldCenter(), true);
}

void Car::turnLeft(){
    if (_isMoving)
        //_carBody->ApplyLinearImpulse(b2Vec2(-2, 0), _carBody->GetWorldCenter(), true);
        _carBody->ApplyAngularImpulse(2, true);
}

void Car::turnRight(){
    if (_isMoving)
        //_carBody->ApplyLinearImpulse(b2Vec2(2, 0), _carBody->GetWorldCenter(), true);
        _carBody->ApplyTorque(-2, true);
}

void Car::updateTraction(){
    if (_onTrack) {
        _currentTraction = 0.3f;
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

void Car::handleInput(Input movInput, Input turnInput){
    CarMovingState* state = _state->handleInput(*this, movInput);
    if (state != NULL){
        delete _state;
        _state = state;
    }
    CarTurningState* turningState = _turningState->handleInput(*this, turnInput);
    if (turningState != NULL){
        delete _turningState;
        _turningState = turningState;
    }
}

void Car::update(){
    _state->update(*this);
    _turningState->update(*this);
}

const float Car::x(){
    return _carBody->GetPosition().x;
}

const float Car::y(){
    return _carBody->GetPosition().y;
}

const float Car::angle(){
    return _carBody->GetAngle();
}

const float Car::speed(){
    return sqrt(pow(linearVelocity().x, 2) + pow(linearVelocity().y, 2)) ;
}

const b2Vec2 Car::linearVelocity(){
    return _carBody->GetLinearVelocity();
}

b2Body* Car::body() const {
    return _carBody;
}

Car::~Car(){
    delete _state;
}

//////////////////////// CAR MOVING STATE ///////////////////////////

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
        //Rozamiento con el piso???
        //car.friction();
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

//////////////////////// CAR TURNING STATE ///////////////////////////

class NotTurningState : public CarTurningState{
public:
    CarTurningState* handleInput(Car& car, Input input){
        return makeTurningState(PRESS_NONE, input);
    }

    void update(Car& car){
        //Continue in straight direction
    }
};

class TurningLeftState : public CarTurningState {
public:
    CarTurningState* handleInput(Car& car, Input input){
        return makeTurningState(PRESS_LEFT, input);
    }

    void update(Car& car){
        //Turn left
        car.turnLeft();
    }
};

class TurningRightState : public CarTurningState {
public:
    CarTurningState* handleInput(Car& car, Input input){
        return makeTurningState(PRESS_RIGHT, input);
    }

    void update(Car& car){
        //Turn right
        car.turnRight();
    }
};

CarTurningState* CarTurningState::makeTurningState(Input prevInput, Input currentInput){
    if (prevInput == PRESS_NONE && currentInput == PRESS_NONE){
        return new NotTurningState();
    } else if (prevInput == PRESS_NONE && currentInput == PRESS_RIGHT) {
        return new TurningRightState();
    } else if(prevInput == PRESS_NONE && currentInput == PRESS_LEFT) {
        return new TurningLeftState();
    } else if (prevInput == PRESS_LEFT && currentInput == PRESS_RIGHT) {
        return new TurningRightState();
    } else if (prevInput == PRESS_LEFT && currentInput == RELEASE_LEFT) {
        return new NotTurningState();
    } else if (prevInput == PRESS_RIGHT && currentInput == RELEASE_RIGHT) {
        return new NotTurningState;
    } else if (prevInput == PRESS_RIGHT && currentInput == PRESS_LEFT) {
        return new TurningLeftState();
    }

    return nullptr;
}