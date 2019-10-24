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
    b2Vec2 normal = _body->GetWorldVector(b2Vec2(1, 0));
    return b2Dot(normal, _body->GetLinearVelocity()) * normal;
}

void Tire::updateFriction(){
    b2Vec2 impulse = _body->GetMass() * -getLateralVelocity();
    _body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
}

Tire::~Tire(){
    _body->GetWorld()->DestroyBody(_body);
}