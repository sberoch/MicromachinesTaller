#include <iostream>
#include "Car.h"
#include "../FixtureUserData.h"

void Car::_setShapeAndFixture(const std::shared_ptr<Configuration>& configuration){
    b2PolygonShape boxShape;
    boxShape.SetAsBox(configuration->getCarWidth(),configuration->getCarHeight());

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = configuration->getCarDensity();
    boxFixtureDef.friction = configuration->getCarFriction();
    _fixture = _carBody->CreateFixture(&boxFixtureDef);
    _fixture->SetUserData(cFUD.get());
}

void Car::_setBodyDef(float x_init, float y_init, float angle, const std::shared_ptr<Configuration>& configuration){
    _carBodyDef.type = b2_dynamicBody;
    _carBodyDef.linearDamping = configuration->getLinearDamping();
    _carBodyDef.angularDamping = configuration->getAngularDamping();
    _carBodyDef.position.Set(x_init, y_init);
    _carBodyDef.angle = angle;
}

Car::Car(std::shared_ptr<b2World> world, size_t id, float x_init, float y_init, float angle, const std::shared_ptr<Configuration>& configuration) :
        _id(id), _previous_x(x_init), _previous_y(y_init), _previousAngle(0),
        _maxHealth(configuration->getCarMaxHealth()),
        _health(configuration->getCarMaxHealth()),
        _maxForwardSpeed(60),
        _maxBackwardSpeed(-10),
        _maxDriveForce(20),
        _desiredTorque(25),
        _maxLateralImpulse(configuration->getCarMaxLateralImpulse()),
        _angularImpulse(configuration->getCarAngularImpulse()),
        _onGrass(false), _isMoving(false), _exploded(false),
        _tracks(),  _groundArea(),
        _currentTraction(1), _status(),
        _maxLaps(1), _maxtracksToLap(20), _laps(0), _winner(false),
        cFUD(new CarFUD(_id)){
    _setBodyDef(x_init, y_init, angle, configuration);
    _carBody = world->CreateBody(&_carBodyDef);
    _carBody->SetLinearVelocity( b2Vec2( configuration->getLinearVelocityInit(), configuration->getLinearVelocityInit() ) ); //not moving
    _carBody->SetAngularVelocity( configuration->getAngularVelocityInit() );

    _setShapeAndFixture(configuration);

    _state = CarMovingState::makeMovingState(STOP_ACCELERATING);
    _turningState = CarTurningState::makeTurningState(STOP_TURNING_RIGHT);

    _carBody->SetUserData(this);
}

void Car::setTrack(Track* track){
    for (size_t i=0; i<_tracks.size(); ++i){
        if (_tracks[i]->equals(track))
            return;
    }
    _tracks.push_back(track);
}

void Car::resetCar(){
    _health = _maxHealth;
    if (_tracks.back()){
        b2Vec2 position = b2Vec2(_tracks.back()->x(), _tracks.back()->y());
        float angleCorrection = 0;
        if (_tracks.back()->type() == TYPE_CURVE_TRACK)
            angleCorrection = 45 * DEGTORAD;
        _carBody->SetTransform(position, _tracks.back()->angle() + angleCorrection);
        _carBody->SetLinearVelocity(b2Vec2(0, 0));
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
    _isMoving = true;

    //find current speed in forward direction
    b2Vec2 currentForwardNormal = _carBody->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

    //apply necessary force
    float force = 0;
    if (_maxForwardSpeed > currentSpeed)
        force = _maxDriveForce;
    else if (_maxForwardSpeed < currentSpeed)
        force = -_maxDriveForce;
    else
        return;
    _carBody->ApplyForce(force * currentForwardNormal, _carBody->GetWorldCenter(), true);
}

void Car::desaccelerate(){
    _isMoving = true;

    //find current speed in forward direction
    b2Vec2 currentForwardNormal = _carBody->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

    //apply necessary force
    float force = 0;
    if ( _maxBackwardSpeed > currentSpeed )
        force = 15;
    else if ( _maxBackwardSpeed < currentSpeed )
        force = -15;
    else
        return;
    _carBody->ApplyForce(force * currentForwardNormal, _carBody->GetWorldCenter(), true);
}

void Car::turnLeft(){
    if (_isMoving)
        _carBody->ApplyTorque( -_desiredTorque, true );
}

void Car::turnRight(){
    if (_isMoving)
        _carBody->ApplyTorque( _desiredTorque, true );
}

void Car::updateFriction(){
    b2Vec2 impulse = _carBody->GetMass() * -getLateralVelocity();
    if (impulse.Length() > _maxLateralImpulse)
        impulse *= _maxLateralImpulse / impulse.Length();
    _carBody->ApplyLinearImpulse(impulse, _carBody->GetWorldCenter(), true);
    _carBody->ApplyAngularImpulse(_angularImpulse * _carBody->GetInertia() * -_carBody->GetAngularVelocity(), true);

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
        std::shared_ptr<Status> status(new Status);
        status->status = ON_GRASS;
        _status.push_back(status);
        _onGrass = true;
    } else {
        _onGrass = false;
    }
}

void Car::removeGroundArea(GroundAreaFUD* ga){
    _groundArea = nullptr;
}

void Car::handleInput(const InputEnum& input){
    std::shared_ptr<CarMovingState> state = _state->handleInput(*this, input);
    if (state != NULL)
        _state = state;
    
    std::shared_ptr<CarTurningState> turningState = _turningState->handleInput(*this, input);
    if (turningState != NULL)
        _turningState = turningState;
}

void Car::update(){
    _state->update(*this);
    _turningState->update(*this);
    updateFriction();
    updateTraction();

    if (_exploded){
        resetCar();
        _exploded = false;
    }

    if (speed() == 0)
        _isMoving = false;

    _previous_x = _carBody->GetPosition().x;
    _previous_y = _carBody->GetPosition().y;

    if (_tracks.size() > 0.8 * _maxtracksToLap && _tracks.back()->isFinish()){
        _laps ++;
        _tracks.clear();
    }

    if (_laps == _maxLaps) {
        _winner;
        std::shared_ptr<Status> status(new Status);
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

void Car::carToDTO(CarDTO_t* carDTO) {
    carDTO->id = _id;
    carDTO->x = this->x();
    carDTO->y = this->y();
    carDTO->angle = this->angle();
    carDTO->health = this->health();
    carDTO->maxForwardSpeed = _maxForwardSpeed;
    carDTO->lapsCompleted = _laps;
}

void Car::dtoToModel(const CarDTO_t& carDTO) {
    _health = carDTO.health;
    _maxForwardSpeed = carDTO.maxForwardSpeed;
    _laps = carDTO.lapsCompleted;
}

b2Body* Car::body() const {
    return _carBody;
}

const bool Car::onGrass(){
    return _onGrass;
}

void Car::crash(b2Vec2 impactVel){
    float vel = sqrt(pow(impactVel.x, 2) + pow(impactVel.y, 2));
    _health -= 2 * vel;

    if (_health <= 0){
        _exploded = true;
        std::shared_ptr<Status> status(new Status);
        status->status = EXPLODED;
        _status.push_back(status);
    }
}

void Car::handleHealthPowerup(size_t id){
    std::shared_ptr<Status> status(new Status);
    status->status = GRABBED_HEALTH_POWERUP;
    status->id = id;
    _status.push_back(status);

    if ((_health + 10) < _maxHealth)
        _health += 10;
    else
        _health = _maxHealth;
}

void Car::handleBoostPowerup(BoostPowerupFUD* bpuFud, size_t id){
    std::shared_ptr<Status> status(new Status);
    status->status = GRABBED_BOOST_POWERUP;
    status->timeOfAction = bpuFud->getActionTime();
    status->id = id;
    _status.push_back(status);

    _maxForwardSpeed += 100;//bpuFud->getSpeedToIncrease();
    _maxDriveForce = 30;
}

void Car::handleMud(MudFUD* mudFud, size_t id){
    std::shared_ptr<Status> status(new Status);
    status->status = GRABBED_MUD;
    status->id = id;
    _status.push_back(status);
}

void Car::handleOil(OilFUD* oilFud, size_t id){
    std::shared_ptr<Status> status(new Status);
    status->status = GRABBED_OIL;
    status->id = id;
    status->timeOfAction = oilFud->getActionTime();
    _status.push_back(status);

    _angularImpulse = 0;
    float randImpulse = -1 + static_cast <float> (std::rand()) /( static_cast <float> (RAND_MAX/(1-(-1))));
    _carBody->ApplyAngularImpulse(randImpulse, true);
}

void Car::handleRock(RockFUD* rockFud, size_t id){
    std::shared_ptr<Status> status(new Status);
    status->status = GRABBED_ROCK;
    status->id = id;
    _status.push_back(status);
    float velToReduce = rockFud->getVelToReduce();
    int healthToReduce = rockFud->getHealthToReduce();

    if (_health < healthToReduce){
        _exploded = true;
        std::shared_ptr<Status> expStatus(new Status);
        expStatus->status = EXPLODED;
        _status.push_back(expStatus);
    }
    _health -= healthToReduce;
    //TODO Que baje aceleracion
}

void Car::stopEffect(const int& effectType){
    switch (effectType) {
        case TYPE_BOOST_POWERUP :
            _maxForwardSpeed -= 100;
            _maxDriveForce = 20;
            break;
        case TYPE_OIL :
            _angularImpulse = 0.9;
            break;
        case TYPE_GRASS :
            //If it is still in grass after n steps reduce vel in half
            break;
    }
}

std::vector<std::shared_ptr<Status>> Car::getStatus(){
    return _status;
}

void Car::resetStatus(){
    _status.clear();
}

Car::~Car(){
    _carBody->GetWorld()->DestroyBody(_carBody);
}

void Car::assignId(int id) {
    this->_id = id;
}

//////////////////////// CAR MOVING STATE ///////////////////////////

class NegAcceleratingState : public CarMovingState {
public:
    std::shared_ptr<CarMovingState> handleInput(Car& car, const InputEnum& input){
        return makeMovingState(input);
    }

    void update(Car& car){
        car.desaccelerate();
    }
};

class AcceleratingState : public CarMovingState {
public:
    std::shared_ptr<CarMovingState> handleInput(Car& car, const InputEnum& input){
        return makeMovingState(input);
    }

    void update(Car& car) {
        //Accelerate
        car.accelerate();
    }
};

class WithoutAcceleratingState : public CarMovingState {
public:
    std::shared_ptr<CarMovingState> handleInput(Car& car, const InputEnum& input){
        return makeMovingState(input);
    }

    void update(Car& car) {
        //Rozamiento con el piso???
        //car.friction();
    }
};

std::shared_ptr<CarMovingState> CarMovingState::makeMovingState(const InputEnum& input){
    if (input == STOP_ACCELERATING || input == STOP_DESACCELERATING){
        return std::shared_ptr<CarMovingState>(new WithoutAcceleratingState());
    } else if (input == ACCELERATE) {
        return std::shared_ptr<CarMovingState>(new AcceleratingState());
    } else if(input == DESACCELERATE) {
        return std::shared_ptr<CarMovingState>(new NegAcceleratingState());
    }
    return nullptr;
}


//////////////////////// CAR TURNING STATE ///////////////////////////

class NotTurningState : public CarTurningState{
public:
    std::shared_ptr<CarTurningState> handleInput(Car& car, const InputEnum& input){
        return makeTurningState(input);
    }

    void update(Car& car){
        //Continue in straight direction

    }
};

class TurningLeftState : public CarTurningState {
public:
    std::shared_ptr<CarTurningState> handleInput(Car& car, const InputEnum& input){
        return makeTurningState(input);
    }

    void update(Car& car){
        //Turn left
        car.turnLeft();
    }
};

class TurningRightState : public CarTurningState {
public:
    std::shared_ptr<CarTurningState> handleInput(Car& car, const InputEnum& input){
        return makeTurningState(input);
    }

    void update(Car& car){
        //Turn right
        car.turnRight();
    }
};

std::shared_ptr<CarTurningState> CarTurningState::makeTurningState(const InputEnum& input){
    if (input == STOP_TURNING_LEFT || input == STOP_TURNING_RIGHT) {
        return std::shared_ptr<CarTurningState>(new NotTurningState());
    } else if (input == TURN_RIGHT) {
        return std::shared_ptr<CarTurningState>(new TurningRightState());
    } else if(input == TURN_LEFT) {
        return std::shared_ptr<CarTurningState>(new TurningLeftState());
    }

    return nullptr;
}
