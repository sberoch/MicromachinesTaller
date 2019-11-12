#include <iostream>
#include "Car.h"
#include "../FixtureUserData.h"

void Car::_setShapeAndFixture(std::shared_ptr<Configuration> configuration){
    b2PolygonShape boxShape;
    boxShape.SetAsBox(configuration->getCarWidth(),configuration->getCarHeight());

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.friction = 0.5f;
    _fixture = _carBody->CreateFixture(&boxFixtureDef);
    _fixture->SetUserData(new CarFUD(_id));
}

void Car::_setBodyDef(float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration){
    _carBodyDef.type = b2_dynamicBody;
    _carBodyDef.linearDamping = configuration->getLinearDamping();
    _carBodyDef.angularDamping = configuration->getAngularDamping();
    _carBodyDef.position.Set(x_init, y_init);
    _carBodyDef.angle = angle;
}

Car::Car(b2World* world, size_t id, float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration) :
        _id(id), _previous_x(x_init), _previous_y(y_init), _previousAngle(0), _health(100),
        _maxForwardSpeed(30),
        _maxBackwardSpeed(-3), _maxDriveForce(25), _desiredTorque(5),
        _isMoving(false), _exploded(false), _currentTrack(nullptr),
        _currentTraction(1), _groundArea(), _status(),
        _maxLaps(3), _maxtracksToLap(20), _tracksCounted(0), _winner(false) {
    _setBodyDef(x_init, y_init, angle, configuration);
    _carBody = world->CreateBody(&_carBodyDef);
    _carBody->SetLinearVelocity( b2Vec2( configuration->getLinearVelocityInit(), configuration->getLinearVelocityInit() ) ); //not moving
    _carBody->SetAngularVelocity( configuration->getAngularVelocityInit() );

    _setShapeAndFixture(configuration);

    _state = CarMovingState::makeMovingState(STOP_ACCELERATING);
    _turningState = CarTurningState::makeTurningState(STOP_TURNING_RIGHT);

    _carBody->SetUserData(this);
}

Car::Car(Car&& other){
    this->_maxForwardSpeed = other._maxForwardSpeed;
    this->_maxBackwardSpeed = other._maxBackwardSpeed;
    this->_maxDriveForce = other._maxDriveForce;
    this->_id = other._id;
    this->_carBodyDef = other._carBodyDef;
    this->_carBody = other._carBody;
    this->_state = other._state;
    this->_turningState = other._turningState;
    this->_isMoving = other._isMoving;
    this->_health = other._health;
    this->_previous_x = other._previous_x;
    this->_previous_y = other._previous_y;
    this->_groundArea = other._groundArea;
    this->_currentTraction = other._currentTraction;

    other._maxForwardSpeed = 0;
    other._maxDriveForce = 0;
    other._id = 0;
    //other._carBodyDef = nullptr;
    other._carBody = nullptr;
    other._state = nullptr;
    other._turningState = nullptr;
    other._isMoving = false;
    other._health = 0;
    other._previous_x = 0;
    other._previous_y = 0;
    other._groundArea = nullptr;
    other._currentTraction = 0;
}

Car& Car::operator=(Car&& other){
    if (this == &other){
        return *this;
    }
    if (this->_carBody)
        free(this->_carBody);
    if (this->_state)
        free(this->_state);
    if (this->_turningState)
        free(this->_turningState);
    this->_maxForwardSpeed = other._maxForwardSpeed;
    this->_maxBackwardSpeed = other._maxBackwardSpeed;
    this->_maxDriveForce = other._maxDriveForce;
    this->_id = other._id;
    this->_carBodyDef = other._carBodyDef;
    this->_carBody = other._carBody;
    this->_state = other._state;
    this->_turningState = other._turningState;
    this->_isMoving = other._isMoving;
    this->_health = other._health;
    this->_previous_x = other._previous_x;
    this->_previous_y = other._previous_y;
    this->_groundArea = other._groundArea;
    this->_currentTraction = other._currentTraction;

    other._maxForwardSpeed = 0;
    other._maxDriveForce = 0;
    other._id = 0;
    //other._carBodyDef = nullptr;
    other._carBody = nullptr;
    other._state = nullptr;
    other._turningState = nullptr;
    other._isMoving = false;
    other._health = 0;
    other._previous_x = 0;
    other._previous_y = 0;
    other._groundArea = nullptr;
    other._currentTraction = 0;

    return *this;
}

void Car::setTrack(Track* track){
    if (_currentTrack && !track->equals(_currentTrack)){
        std::cout << "\nTracks counted " << _tracksCounted << '\n';
        _tracksCounted ++;
    }
    _currentTrack = track;
}

void Car::resetCar(){
    _health = 100;
    if (_currentTrack){
        std::cout << "\nExploded, putting in center of track\n";
        b2Vec2 position = b2Vec2(_currentTrack->x(), _currentTrack->y());
        _carBody->SetTransform(position, _currentTrack->angle() + 90 * DEGTORAD);
    } else {
        b2Vec2 position = b2Vec2(_previous_x, _previous_y);
        _carBody->SetTransform(position, _previousAngle);
    }
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
    //std::cout << "Acelerando ";
    _isMoving = true;
    float desiredSpeed = _maxForwardSpeed;

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
    _carBody->ApplyForce(_currentTraction * force * currentForwardNormal, _carBody->GetWorldCenter(), true);
    //std::cout << "  x " << x() << " y " << y() << " angle" << angle() << '\n';
}

void Car::desaccelerate(){
    //std::cout << "Descelerando ";
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
    _carBody->ApplyForce(_currentTraction * force * currentForwardNormal, _carBody->GetWorldCenter(), true);
    //std::cout << "x " << x() << " y " << y() << " angle" << angle()<< '\n';
}

void Car::turnLeft(){
    //std::cout << "\nTurn left";
    float desiredTorque = -_desiredTorque;
    if (_isMoving)
        _carBody->ApplyTorque( desiredTorque, true );
    //std::cout << " x " << x() << " y " << y() << " angle" << angle();
}

void Car::turnRight(){
    //std::cout << "\nTurn right";
    float desiredTorque = _desiredTorque;
    if (_isMoving)
        _carBody->ApplyTorque( desiredTorque, true );
    //std::cout << " x " << x() << " y " << y() << " angle" << angle();
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
    if (_groundArea)
        _currentTraction = _groundArea->frictionModifier;
    else
        _currentTraction = 1;
}

void Car::addGroundArea(GroundAreaFUD* ga){
    _groundArea = ga;
    if (ga->grass){
        Status* status = new Status;
        status->status = ON_GRASS;
        _status.push_back(status);
    }
    std::cout << "Added gd with " << _groundArea->frictionModifier ;
}

void Car::removeGroundArea(GroundAreaFUD* ga){
    _groundArea = nullptr;
    std::cout << "No more ga\n";
}

void Car::handleInput(const InputEnum& input){
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
    updateFriction();
    updateTraction();

    if (_exploded)
        resetCar();

    if (speed() == 0)
        _isMoving = false;

    _previous_x = _carBody->GetPosition().x;
    _previous_y = _carBody->GetPosition().y;

    if (_tracksCounted > 0.8 * _maxtracksToLap * _maxLaps) {
        std::cout << "\nWINNER!!!!!!!!!!!!!!!!!!!!!!!\n";
        _winner;
        Status* status = new Status;
        status->status = WINNED;
        _status.push_back(status);
    }
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

//TODO que impacten bien y que al llegar a cero explote
void Car::crash(b2Vec2 impactVel){
    std::cout << "\nImpact vel: " << impactVel.x << ' ' << impactVel.y ;
    float vel = sqrt(pow(impactVel.x, 2) + pow(impactVel.y, 2));
    _health -= 2 * vel;
    std::cout << "\nHealth: " << _health;
    if (_health <= 0){
        _exploded = true;
        Status* status = new Status;
        status->status = EXPLODED;
        _status.push_back(status);
        std::cout << "Health is 0\n";
    }
}

void Car::handleHealthPowerup(size_t id){
    Status* status = new Status;
    status->status = GRABBED_HEALTH_POWERUP;
    status->id = id;
    _status.push_back(status);
    std::cout << "\nHealth bhp: " << _health;
    if ((_health + 10) < 100)
        _health += 10;
    std::cout << "\nHealth ahp: " << _health;
}

void Car::handleBoostPowerup(BoostPowerupFUD* bpuFud, size_t id){
    Status* status = new Status;
    status->status = GRABBED_BOOST_POWERUP;
    status->timeOfAction = bpuFud->getActionTime();
    status->id = id;
    _status.push_back(status);
    std::cout << "Max speed bbp: " << _maxForwardSpeed << ' ';
    _maxForwardSpeed += bpuFud->getSpeedToIncrease();
    std::cout << "Max speed abp: " << _maxForwardSpeed << '\n';
    //Ver como ponerlo por un rato nada mas
}

void Car::handleMud(MudFUD* mudFud, size_t id){
    Status* status = new Status;
    status->status = GRABBED_MUD;
    status->id = id;
    _status.push_back(status);
}

void Car::handleOil(OilFUD* oilFud, size_t id){
    Status* status = new Status;
    status->status = GRABBED_OIL;
    status->id = id;
    _status.push_back(status);
    float damping = oilFud->getDamping();

    //_carBody->SetLinearDamping(damping);
}

void Car::handleRock(RockFUD* rockFud, size_t id){
    Status* status = new Status;
    status->status = GRABBED_ROCK;
    status->id = id;
    _status.push_back(status);
    float velToReduce = rockFud->getVelToReduce();
    int healthToReduce = rockFud->getHealthToReduce();

    _health -= healthToReduce;
    _maxForwardSpeed -= velToReduce; //???
}

void Car::stopEffect(const int& effectType){
    switch (effectType) {
        case TYPE_BOOST_POWERUP :
            _maxForwardSpeed += 10;
            break;
        case TYPE_OIL :
            break;
        case TYPE_GRASS :
            //TODO see how to do this
            //If it is still in grass after n steps reduce vel in half
            //See distance with track
            break;
    }
}

std::vector<Status*> Car::getStatus(){
    return _status;
}

void Car::resetStatus(){
    for (size_t i=0; i<_status.size(); ++i){
        delete _status[i];
    }
    _status.clear(); //No se si es necesario
}

Car::~Car(){
    _carBody->GetWorld()->DestroyBody(_carBody);
    delete _state;
    delete _turningState;
}

//////////////////////// CAR MOVING STATE ///////////////////////////

class NegAcceleratingState : public CarMovingState {
public:
    CarMovingState* handleInput(Car& car, const InputEnum& input){
        return makeMovingState(input);
    }

    void update(Car& car){
        car.desaccelerate();
    }
};

class AcceleratingState : public CarMovingState {
public:
    CarMovingState* handleInput(Car& car, const InputEnum& input){
        return makeMovingState(input);
    }

    void update(Car& car) {
        //Accelerate
        car.accelerate();
    }
};

class WithoutAcceleratingState : public CarMovingState {
public:
    CarMovingState* handleInput(Car& car, const InputEnum& input){
        return makeMovingState(input);
    }

    void update(Car& car) {
        //Rozamiento con el piso???
        //car.friction();
    }
};

CarMovingState* CarMovingState::makeMovingState(const InputEnum& input){
    if (input == STOP_ACCELERATING || input == STOP_DESACCELERATING){
        return new WithoutAcceleratingState();
    } else if (input == ACCELERATE) {
        return new AcceleratingState();
    } else if(input == DESACCELERATE) {
        return new NegAcceleratingState();
    }
    return nullptr;
}


//////////////////////// CAR TURNING STATE ///////////////////////////

class NotTurningState : public CarTurningState{
public:
    CarTurningState* handleInput(Car& car, const InputEnum& input){
        return makeTurningState(input);
    }

    void update(Car& car){
        //Continue in straight direction

    }
};

class TurningLeftState : public CarTurningState {
public:
    CarTurningState* handleInput(Car& car, const InputEnum& input){
        return makeTurningState(input);
    }

    void update(Car& car){
        //Turn left
        car.turnLeft();
    }
};

class TurningRightState : public CarTurningState {
public:
    CarTurningState* handleInput(Car& car, const InputEnum& input){
        return makeTurningState(input);
    }

    void update(Car& car){
        //Turn right
        car.turnRight();
    }
};

CarTurningState* CarTurningState::makeTurningState(const InputEnum& input){
    if (input == STOP_TURNING_LEFT || input == STOP_TURNING_RIGHT) {
        return new NotTurningState();
    } else if (input == TURN_RIGHT) {
        return new TurningRightState();
    } else if(input == TURN_LEFT) {
        return new TurningLeftState();
    }

    return nullptr;
}
