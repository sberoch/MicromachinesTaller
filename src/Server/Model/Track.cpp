#include "../json/json.hpp"
#include <fstream>
#include <iostream>
#include "Track.h"
#include "FixtureUserData.h"

void Track::_setBodyDef(float x_init, float y_init, float angle_init, std::shared_ptr<Configuration> configuration){
    _bodyDef.type = b2_staticBody;
    _bodyDef.position.Set(x_init, y_init);
    _bodyDef.angle = angle_init;
}

void Track::_setFixtureDef(std::shared_ptr<Configuration> configuration){
    b2PolygonShape shape;
    shape.SetAsBox(configuration->getTrackWidth(), configuration->getTrackHeight());
    _fixtureDef.shape = &shape;
    _fixtureDef.density = configuration->getTrackDensity();
    _fixtureDef.friction = configuration->getTrackFriction();
    _fixtureDef.restitution = configuration->getTrackRestitution();
    _fixtureDef.isSensor = true;
    _fixture = _body->CreateFixture(&_fixtureDef);
    _fixture->SetUserData(new GroundAreaFUD(0.9f, false, _id));
}

Track::Track(b2World* world, size_t id, int type, float x_init, float y_init, float angle_init, std::shared_ptr<Configuration> configuration) :
             _id(id), _type(type), _fixtureDef() {
    _setBodyDef(x_init, y_init, angle_init, configuration);
    _body = world->CreateBody(&_bodyDef);
    _setFixtureDef(configuration);

    _body->SetUserData(this);
}

const float Track::x(){
    return _body->GetPosition().x;
}

const float Track::y(){
    return _body->GetPosition().y;
}

const float Track::angle(){
    return _body->GetAngle();
}

const int Track::type(){
    return _type;
}

bool Track::equals(Track* other){
    if (other->x() == x() && other->y() == y() && other->angle() == angle()){
        return true;
    }
    return false;
}

Track::~Track(){
    _body->GetWorld()->DestroyBody(_body);
}
