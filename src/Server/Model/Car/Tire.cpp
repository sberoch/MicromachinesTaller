#include "Tire.h"

Tire::Tire(b2World* world){
    _bodyDef.type = b2_dynamicBody;
    _body = world->CreateBody(&_bodyDef);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(0.25f, 0.5f);
    _body->CreateFixture(&polygonShape, 1);

    _body->SetUserData(this);
}

b2Vec2 Tire::getLateralVelocity(){
    b2Vec2 currentRightNormal = _body->GetWorldVector(b2Vec2(1, 0));
    return b2Dot(currentRightNormal, _body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 Tire::getForwardVelocity(){
    b2Vec2 currentForwardNormal = _body->GetWorldVector(b2Vec2(0,1));
    return b2Dot(currentForwardNormal, _body->GetLinearVelocity()) * currentForwardNormal;
}

void Tire::updateFriction(){
    b2Vec2 impulse = _body->GetMass() * -getLateralVelocity();
    _body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
    _body->ApplyAngularImpulse( 0.1f * _body->GetInertia() * -_body->GetAngularVelocity(), true);

    b2Vec2 currentForwardNormal = getForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -2 * currentForwardSpeed;
    _body->ApplyForce(dragForceMagnitude * currentForwardNormal, _body->GetWorldCenter(), true);
}

Tire::~Tire(){
    _body->GetWorld()->DestroyBody(_body);
}