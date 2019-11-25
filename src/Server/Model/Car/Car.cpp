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

void Car::_setBodyDef(float& x_init, float& y_init, float& angle, const std::shared_ptr<Configuration>& configuration){
    _carBodyDef.type = b2_dynamicBody;
    _carBodyDef.linearDamping = configuration->getLinearDamping();
    _carBodyDef.angularDamping = configuration->getAngularDamping();
    _carBodyDef.position.Set(x_init, y_init);
    _carBodyDef.angle = angle;
}


Car::Car(const std::shared_ptr<b2World>& world, size_t& id, float& x_init, float& y_init, float angle,
         const size_t& max_tracks, const std::shared_ptr<Configuration>& configuration) :
        _id(id), _previous_x(x_init), _previous_y(y_init), _previousAngle(0),
        _maxHealth(configuration->getCarMaxHealth()),
        _health(configuration->getCarMaxHealth()),
        _maxForwardSpeed(configuration->getMaxForwardSpeed()),
        _maxBackwardSpeed(configuration->getMaxBackwardsSpeed()),
        _maxForwardDrive(configuration->getMaxForwardDrive()),
        _maxBackwardDrive(configuration->getMaxBackwardDrive()),
        _maxForwardSpeedOnGrass(configuration->getMaxForwardSpeedOnGrass()),
        _maxForwardDriveOnGrass(configuration->getMaxForwardDriveOnGrass()),
        _maxBackwardSpeedOnGrass(configuration->getMaxBackwardSpeedOnGrass()),
        _maxBackwardDriveOnGrass(configuration->getMaxBackwardDriveOnGrass()),
        _currentForwardSpeed(configuration->getMaxForwardSpeed()),
        _currentForwardDrive(configuration->getMaxForwardDrive()),
        _currentBackwardSpeed(configuration->getMaxBackwardsSpeed()),
        _currentBackwardDrive(configuration->getMaxBackwardDrive()),
        _desiredTorque(configuration->getCarDesiredTorque()),
        _maxLateralImpulse(configuration->getCarMaxLateralImpulse()),
        _maxAngularImpulse(configuration->getCarAngularImpulse()), _angularImpulse(configuration->getCarAngularImpulse()),
        _onGrass(false), _isMoving(false), _exploded(false),
        _tracks(),  _groundArea(), _status(),
        _maxLaps(configuration->getMaxLaps()), _maxtracksToLap(max_tracks), _laps(0), _winner(false),
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
    if (!_tracks.empty() && _tracks.back()->isFinish())
        _tracks.clear();
    for (auto & _track : _tracks){
        if (_track->equals(track))
            return;
    }
    _tracks.push_back(track);
}

void Car::resetCar() {
    _health = _maxHealth;
    if (_tracks.back()){
        b2Vec2 position = b2Vec2(_tracks.back()->x(), _tracks.back()->y());
        float angleCorrection = 180 * DEGTORAD;
        if (_tracks.back()->type() == TYPE_CURVE_TRACK)
            angleCorrection = (45 + 180) * DEGTORAD;
        _carBody->SetTransform(position, _tracks.back()->angle() + angleCorrection);
        _carBody->SetLinearVelocity(b2Vec2(0, 0));
    } else {
        b2Vec2 position = b2Vec2(_previous_x, _previous_y);
        _carBody->SetTransform(position, _previousAngle);
    }
}

void Car::explode(){
    _exploded = true;
    std::shared_ptr<Status> expStatus(new Status);
    expStatus->status = EXPLODED;
    _status.push_back(expStatus);
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
    if (_currentForwardDrive < 0)
        return;

    float force = 0;
    if (_currentForwardSpeed > currentSpeed)
        force = _currentForwardDrive;
    else if (_currentForwardSpeed < currentSpeed)
        force = -_currentForwardDrive;
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
    if (_currentBackwardDrive < 0)
        return;

    float force = 0;
    if ( _currentBackwardSpeed > currentSpeed )
        force = _currentBackwardDrive;
    else if ( _currentBackwardSpeed < currentSpeed )
        force = -_currentBackwardDrive;
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

void Car::modifySpeed(const bool& onGrass, float& speedToModify, float& maxSpeedOnGrass, float& maxSpeedOnTrack,
                      float& driveToModify, float& maxDriveOnGrass, float& maxDriveOnTrack) {
    float speedModifier = 0;
    float driveModifier = 0;
    if (this->onGrass()){
        speedModifier = speedToModify - maxSpeedOnGrass;
        driveModifier = driveToModify - maxDriveOnGrass;
    } else {
        speedModifier = speedToModify - maxSpeedOnTrack;
        driveModifier = driveToModify - maxDriveOnTrack;
    }

    if (onGrass){
        _onGrass = true;
        (maxSpeedOnGrass + speedModifier > 0) ? (speedToModify = maxSpeedOnGrass + speedModifier) : (speedToModify = maxSpeedOnGrass);
        (maxDriveOnGrass + driveModifier > 0) ? (driveToModify = maxDriveOnGrass + driveModifier) : (driveToModify = maxDriveOnGrass);
    } else {
        _onGrass = false;
        (maxSpeedOnTrack + speedModifier > 0) ? (speedToModify = maxSpeedOnTrack + speedModifier) : (speedToModify = maxSpeedOnTrack);
        (maxDriveOnTrack + driveModifier > 0) ? (driveToModify = maxDriveOnTrack + driveModifier) : (driveToModify = maxDriveOnTrack);
    }
}

void Car::addGroundArea(GroundAreaFUD* ga){
    _groundArea = ga;

    modifySpeed(ga->isGrass(), _currentForwardSpeed, _maxForwardSpeedOnGrass, _maxForwardSpeed,
                _currentForwardDrive, _maxForwardDriveOnGrass, _maxForwardDrive);
    modifySpeed(ga->isGrass(), _currentBackwardSpeed, _maxBackwardSpeedOnGrass, _maxBackwardSpeed,
                _currentBackwardDrive, _maxBackwardDriveOnGrass, _maxBackwardDrive);
}

void Car::removeGroundArea(GroundAreaFUD* ga){
    _groundArea = nullptr;
}

void Car::handleInput(const InputEnum& input){
    std::shared_ptr<CarMovingState> state = _state->handleInput(*this, input);
    if (state != nullptr)
        _state = state;
    
    std::shared_ptr<CarTurningState> turningState = _turningState->handleInput(*this, input);
    if (turningState != nullptr)
        _turningState = turningState;
}

int Car::update(){
    _state->update(*this);
    _turningState->update(*this);
    updateFriction();

    if (_exploded){
        resetCar();
        _exploded = false;
    }

    if (speed() < 0.1)
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
    return _laps;
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
    carDTO->maxForwardDrive = _currentForwardDrive;
    carDTO->lapsCompleted = _laps;
}

void Car::dtoToModel(const CarDTO_t& carDTO) {
    _health = carDTO.health;
    _currentForwardDrive = carDTO.maxForwardDrive;
    _laps = carDTO.lapsCompleted;
}

const bool Car::onGrass(){
    return _onGrass;
}

void Car::crash(b2Vec2 impactVel){
    float vel = sqrt(pow(impactVel.x, 2) + pow(impactVel.y, 2));
    _health -= 2 * vel;

    if (_health <= 0)
        explode();
}

void Car::handleHealthPowerup(HealthPowerupFUD* hpu, const size_t& id){
    std::shared_ptr<Status> status(new Status);
    status->status = GRABBED_HEALTH_POWERUP;
    status->id = id;
    status->timeOfAction = 0;
    _status.push_back(status);

    if ((_health + hpu->getHealthToIncrease()) < _maxHealth)
        _health += hpu->getHealthToIncrease();
    else
        _health = _maxHealth;
}

void Car::handleBoostPowerup(BoostPowerupFUD* bpuFud, const size_t& id){
    std::shared_ptr<Status> status(new Status);
    status->status = GRABBED_BOOST_POWERUP;
    status->timeOfAction = bpuFud->getActionTime();
    status->id = id;
    _status.push_back(status);

    _currentForwardSpeed += bpuFud->getSpeedToIncrease();
    _currentForwardDrive = bpuFud->getNewDrive();
}

void Car::handleMud(MudFUD* mudFud, const size_t& id){
    std::shared_ptr<Status> status(new Status);
    status->status = GRABBED_MUD;
    status->timeOfAction = 0;
    status->id = id;
    _status.push_back(status);
}

void Car::handleOil(OilFUD* oilFud, const size_t& id){
    std::shared_ptr<Status> status(new Status);
    status->status = GRABBED_OIL;
    status->id = id;
    status->timeOfAction = oilFud->getActionTime();
    _status.push_back(status);

    _angularImpulse = 0;
    srand(time(NULL));
    float randImpulse = -1 + static_cast <float> (std::rand()) /( static_cast <float> (RAND_MAX/(1-(-1))));
    _carBody->ApplyAngularImpulse(randImpulse, true);
}

void Car::handleRock(RockFUD* rockFud, const size_t& id){
    std::shared_ptr<Status> status(new Status);
    status->status = GRABBED_ROCK;
    status->timeOfAction = rockFud->getTimeOfAction();
    status->id = id;
    _status.push_back(status);
    float velToReduce = rockFud->getVelToReduce();
    int healthToReduce = rockFud->getHealthToReduce();
    int driveToReduce = rockFud->getDriveToReduce();

    _health -= healthToReduce;
    if (_health <= 0)
        explode();

    if (_currentForwardSpeed > velToReduce && _currentForwardDrive > driveToReduce){
        _currentForwardSpeed -= velToReduce;
        _currentForwardDrive -= driveToReduce;
    }
}

void Car::stopEffect(const int& effectType){
    switch (effectType) {
        case TYPE_BOOST_POWERUP :
            _currentForwardSpeed = (this->onGrass()) ? _maxForwardSpeedOnGrass : _maxForwardSpeed;
            _currentForwardDrive = (this->onGrass()) ? _maxForwardDriveOnGrass : _maxForwardDrive;
            break;
        case TYPE_OIL :
            _angularImpulse = _maxAngularImpulse;
            break;
        case TYPE_ROCK:
            _currentForwardSpeed = (this->onGrass()) ? _maxForwardSpeedOnGrass : _maxForwardSpeed;
            _currentForwardDrive = (this->onGrass()) ? _maxForwardDriveOnGrass : _maxForwardDrive;
            break;
    }
}

std::vector<std::shared_ptr<Status>> Car::getStatus(){
    return _status;
}

void Car::resetStatus(){
    _status.clear();
}

void Car::assignId(int id) {
    this->_id = id;
}




