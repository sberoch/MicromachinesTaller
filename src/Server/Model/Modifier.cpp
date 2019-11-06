#include "Modifier.h"

void Modifier::_setBodyDef(float x_init, float y_init, float angle_init, std::shared_ptr<Configuration> configuration){
    _bodyDef.type = b2_staticBody;
    _bodyDef.position.Set(x_init, y_init);
    _bodyDef.angle = angle_init;
}

void Modifier::_setFixtureDef(std::shared_ptr<Configuration> configuration){
    b2PolygonShape shape;
    shape.SetAsBox(configuration->getTrackWidth(), configuration->getTrackHeight());
    _fixtureDef.shape = &shape;
    _fixtureDef.density = configuration->getTrackDensity();
    _fixtureDef.friction = configuration->getTrackFriction();
    _fixtureDef.restitution = configuration->getTrackRestitution();
    _fixtureDef.isSensor = true; //TODO SEE SENSOR AND CONTACTLISTENER

  //  _fixture = _body->CreateFixture(&_fixtureDef);
//    _fixture->SetUserData();
}

