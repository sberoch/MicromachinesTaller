#include <iostream>
#include "Car.h"

void Car::_setShapeAndFixture(std::shared_ptr<Configuration> configuration){
    b2PolygonShape boxShape;
    boxShape.SetAsBox(configuration->getCarWidth(),configuration->getCarHeight());

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1; //Cuanta densidad?
    _carBody->CreateFixture(&boxFixtureDef);
}
/*
Car::Car(b2Body* carBody) : _health(100), _previous_x(0), _previous_y(0), _maxForwardSpeed(25),
                            _maxBackwardSpeed(-5), _maxDriveForce(50), _isMoving(false),
                            _onTrack(true), _onGrass(false), _currentTraction(1), _carBody(carBody){
    _carBody->SetLinearVelocity( b2Vec2( 0, 0 ) ); //not moving
    _carBody->SetAngularVelocity( 0 );
    _setShapeAndFixture();

    _state = CarMovingState::makeMovingState(PRESS_NONE, PRESS_NONE);
    _turningState = CarTurningState::makeTurningState(PRESS_NONE, PRESS_NONE);

    _carBody->SetUserData(this);
}*/

void Car::_setBodyDef(float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration){
    _carBodyDef.type = b2_dynamicBody;
    _carBodyDef.linearDamping = configuration->getLinearDamping();
    _carBodyDef.angularDamping = configuration->getAngularDamping();
    _carBodyDef.position.Set(x_init, y_init);
    _carBodyDef.angle = angle;
}

Car::Car(b2World* world, size_t id, float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration) :
                                        _id(id), _previous_x(x_init), _previous_y(y_init), _health(100), _maxForwardSpeed(25),
                                        _maxBackwardSpeed(-5), _maxDriveForce(50), _isMoving(false),
                                        _onTrack(true), _onGrass(false), _currentTraction(1){
    _setBodyDef(x_init, y_init, angle, configuration);
    _carBody = world->CreateBody(&_carBodyDef);
    _carBody->SetLinearVelocity( b2Vec2( configuration->getLinearVelocityInit(), configuration->getLinearVelocityInit() ) ); //not moving
    _carBody->SetAngularVelocity( configuration->getAngularVelocityInit() );
    _setShapeAndFixture(configuration);

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
    std::cout << "Acelerando\n";
    _isMoving = true;
    float desiredSpeed = _maxForwardSpeed;
    std::cout << "max speed " << _maxForwardSpeed;

    //find current speed in forward direction
    b2Vec2 currentForwardNormal = _carBody->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

    //apply necessary force
    float force = 0;
    if (desiredSpeed > currentSpeed)
        force = _maxDriveForce;
    else if (desiredSpeed < currentSpeed)
        force = -_maxDriveForce;
    else
        return;
    _carBody->ApplyForce(force * currentForwardNormal, _carBody->GetWorldCenter(), true);
}

void Car::desaccelerate(){
    std::cout << "Descelerando\n";
    _isMoving = true;
    float desiredSpeed = _maxBackwardSpeed;

    //find current speed in forward direction
    b2Vec2 currentForwardNormal = _carBody->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

    //apply necessary force
    float force = 0;
    if ( desiredSpeed > currentSpeed )
        force = _maxDriveForce;
    else if ( desiredSpeed < currentSpeed )
        force = -_maxDriveForce;
    else
        return;
    _carBody->ApplyForce(force * currentForwardNormal, _carBody->GetWorldCenter(), true);
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
    std::cout << "Turn left\n";
    float desiredTorque = -50;
    if (_isMoving)
        _carBody->ApplyTorque( desiredTorque, true );
}

void Car::turnRight(){
    std::cout << "Turn right\n";
    float desiredTorque = 50;
    if (_isMoving)
        _carBody->ApplyTorque( desiredTorque, true );
}

void Car::updateFriction(){
    float maxLateralImpulse = 2.5f;
    b2Vec2 impulse = _carBody->GetMass() * -getLateralVelocity();
    if (impulse.Length() > maxLateralImpulse)
        impulse *= maxLateralImpulse / impulse.Length();
    _carBody->ApplyLinearImpulse(impulse, _carBody->GetWorldCenter(), true);
    _carBody->ApplyAngularImpulse(0.9f * _carBody->GetInertia() * -_carBody->GetAngularVelocity(), true);

    b2Vec2 currentForwardNormal = getForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -2 * currentForwardSpeed;
    _carBody->ApplyForce(dragForceMagnitude * currentForwardNormal, _carBody->GetWorldCenter(), true);
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
    updateFriction();
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

const float Car::health(){
    return _health;
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
    _carBody->GetWorld()->DestroyBody(_carBody);
    delete _state;
}

//////////////////////// CAR MOVING STATE ///////////////////////////

class NegAcceleratingState : public CarMovingState {
public:
    CarMovingState* handleInput(Car& car, Input input){
        return makeMovingState(PRESS_DOWN, input);
    }

    void update(Car& car){
        car.desaccelerate();
    }
};

class AcceleratingState : public CarMovingState {
public:
    CarMovingState* handleInput(Car& car, Input input) {
        return makeMovingState(PRESS_UP, input);
    }

    void update(Car& car) {
        //Accelerate
        car.accelerate();
    }
};

class WithoutAcceleratingState : public CarMovingState {
public:
    CarMovingState* handleInput(Car& car, Input input) {
        return makeMovingState(PRESS_NONE, input );
    }

    void update(Car& car) {
        //Rozamiento con el piso???
        //car.friction();
    }
};

CarMovingState* CarMovingState::makeMovingState(Input prevInput, Input currentInput){
    if (prevInput == PRESS_NONE && currentInput == PRESS_NONE){
        return new WithoutAcceleratingState();
    } else if (prevInput == PRESS_NONE && currentInput == PRESS_UP) {
        return new AcceleratingState();
    } else if(prevInput == PRESS_UP && currentInput == PRESS_DOWN) {
        return new NegAcceleratingState();
    } else if (prevInput == PRESS_DOWN && currentInput == PRESS_UP) {
        return new AcceleratingState();
    } else if (prevInput == PRESS_UP && currentInput == RELEASE_UP) {
        return new WithoutAcceleratingState();
    } else if (prevInput == PRESS_DOWN && currentInput == RELEASE_DOWN) {
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