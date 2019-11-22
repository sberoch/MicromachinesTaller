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
    gaFUD = std::make_shared<GroundAreaFUD>(0.9f, false, _id);
    _fixture->SetUserData(gaFUD.get());
}

Track::Track(std::shared_ptr<b2World> world, size_t id, int type, float x_init,
        float y_init, float angle_init, std::shared_ptr<Configuration> configuration) :
             _id(id), _type(type), _fixtureDef(), _start(false), _finish(false){

    _setBodyDef(x_init, y_init, angle_init, configuration);
    _body = world->CreateBody(&_bodyDef);
    _setFixtureDef(configuration);

    _body->SetUserData(this);
}

void Track::setAsStart(){
    _start = true;
}

void Track::setAsFinish(){
    _finish = true;
}

bool Track::isStart(){
    return _start;
}

bool Track::_isBetweenLimits(const float& pos, const char& xOrY){
    float centerOfMass;
    switch (xOrY){
        case 'x' :
            centerOfMass = this->x();
            break;
        case 'y' :
            centerOfMass = this->y();
            break;
        default :
            return false;
    }

    return pos < (centerOfMass + 2.5f) && pos > (centerOfMass - 2.5f);
}

float Track::getDistance(const float& x, const float& y){
    float leftXLim = this->x() - 2.5f;
    float rightXLim = this->x() + 2.5f;
    float upperYLim = this->y() + 2.5f;
    float bottomYLim = this->y() - 2.5f;

    if (_isBetweenLimits(x, 'x') && !_isBetweenLimits(y, 'y')){
        if (y > this->y()) {
            return abs(y - upperYLim);
        } else {
            return abs(bottomYLim - y);
        }
    } else if (!_isBetweenLimits(x, 'x') && _isBetweenLimits(y, 'y')){
        if (x > this->x()) {
            return abs(x - rightXLim);
        } else {
            return abs(leftXLim - x);
        }
    } else if (!_isBetweenLimits(x, 'x') && !_isBetweenLimits(y, 'y')){
        if (x > this->x() && y > this->y()) {
            return sqrt(pow((x - rightXLim), 2) + pow((y - upperYLim), 2));
        } else if (x < this->x() && y > this->y()){
            return sqrt(pow((x - leftXLim), 2) + pow((y - upperYLim), 2));
        } else if (x > this->x() && y < this->y()) {
            return sqrt(pow((x - rightXLim), 2) + pow((y - bottomYLim), 2));
        } else {
            return sqrt(pow((x - leftXLim), 2) + pow((y - bottomYLim), 2));
        }
    }

    return 0;
}

bool Track::isFinish(){
    return _finish;
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
    return other->x() == x() && other->y() == y() && other->angle() == angle();
}

void Track::toDTO(TrackDTO_t* trackDTO) {
    trackDTO->x = this->x();
    trackDTO->y = this->y();
    trackDTO->angle = this->angle();
    trackDTO->halfWidth = 2.5f;
    trackDTO->halfHeight = 2.5f;
    trackDTO->start = this->isStart();
}

