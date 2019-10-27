#include "Tire.h"

Tire::Tire(b2World* world, float maxForwardSpeed, float maxBackwardSpeed, float madDriveForce) :
           _currentTraction(1), _maxForwardSpeed(maxForwardSpeed),
           _maxBackwardSpeed(maxBackwardSpeed), _maxDriveForce(_maxDriveForce){
    _bodyDef.type = b2_dynamicBody;
    _body = world->CreateBody(&_bodyDef);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(0.25f, 0.5f);
    _body->CreateFixture(&polygonShape, 1);

    _body->SetUserData(this);
}

void Tire::addGroundArea(GroundAreaFUD* ga){
    _groundArea = ga;
    updateTraction();
}

void Tire::removeGroundArea(GroundAreaFUD* ga){
    _groundArea = nullptr; // eliminar?
    updateTraction();
}

b2Vec2 Tire::getLateralVelocity(){
    b2Vec2 currentRightNormal = _body->GetWorldVector(b2Vec2(1, 0));
    return b2Dot(currentRightNormal, _body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 Tire::getForwardVelocity(){
    b2Vec2 currentForwardNormal = _body->GetWorldVector(b2Vec2(0,1));
    return b2Dot(currentForwardNormal, _body->GetLinearVelocity()) * currentForwardNormal;
}

void Tire::updateTraction(){
    if (!_groundArea)
        _currentTraction = 1;
    else {
        //find area with highest traction
        _currentTraction = 0;
        if (_groundArea->frictionModifier > _currentTraction)
            _currentTraction = _groundArea->frictionModifier;
    }
}

void Tire::updateDrive(int controlState){
    //find desired speed
    float desiredSpeed = 0;
    switch ( controlState & (PRESS_UP|PRESS_DOWN) ) {
        case PRESS_UP:   desiredSpeed = _maxForwardSpeed;  break;
        case PRESS_DOWN: desiredSpeed = _maxBackwardSpeed; break;
        default: return;//do nothing
    }

    //find current speed in forward direction
    b2Vec2 currentForwardNormal = _body->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot( getForwardVelocity(), currentForwardNormal );

    //apply necessary force
    float force = 0;
    if ( desiredSpeed > currentSpeed )
        force = _maxDriveForce;
    else if ( desiredSpeed < currentSpeed )
        force = -_maxDriveForce;
    else
        return;
    _body->ApplyForce( _currentTraction * force * currentForwardNormal, _body->GetWorldCenter(), true);
}

void Tire::updateTurn(int controlState){
    float desiredTorque = 0;
    switch ( controlState & (PRESS_LEFT|PRESS_RIGHT) ) {
        case PRESS_LEFT:  desiredTorque = 15;  break;
        case PRESS_RIGHT: desiredTorque = -15; break;
        default: ;//nothing
    }
    _body->ApplyTorque( desiredTorque, true );
}

void Tire::updateFriction(){
    float maxLateralImpulse = 2.5f;
    b2Vec2 impulse = _body->GetMass() * -getLateralVelocity();
    if ( impulse.Length() > maxLateralImpulse )
        impulse *= maxLateralImpulse / impulse.Length();
    _body->ApplyLinearImpulse(_currentTraction * impulse, _body->GetWorldCenter(), true);
    _body->ApplyAngularImpulse(_currentTraction * 0.1f * _body->GetInertia() * -_body->GetAngularVelocity(), true);

    b2Vec2 currentForwardNormal = getForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -2 * currentForwardSpeed;
    _body->ApplyForce(_currentTraction * dragForceMagnitude * currentForwardNormal, _body->GetWorldCenter(), true);
}

Tire::~Tire(){
    _body->GetWorld()->DestroyBody(_body);
}