#include <iostream>
#include "Grass.h"
#include "FixtureUserData.h"

void Grass::_setBodyDef(float x_init, float y_init, float angle_init, std::shared_ptr<Configuration> configuration){
    _bodyDef.type = b2_staticBody;
    _bodyDef.position.Set(x_init, y_init);
    _bodyDef.angle = angle_init;
}

void Grass::_setFixtureDef(std::shared_ptr<Configuration> configuration){
    b2PolygonShape shape;
    shape.SetAsBox(configuration->getGrassWidth(), configuration->getGrassHeight());
    _fixtureDef.shape = &shape;
    _fixtureDef.density = configuration->getGrassDensity();
    _fixtureDef.friction = configuration->getGrassFriction();
    _fixtureDef.restitution = configuration->getGrassRestitution();
    _fixtureDef.isSensor = true; //TODO SEE SENSOR AND CONTACTLISTENER

    _body->CreateFixture(&_fixtureDef);

    _fixture = _body->CreateFixture(&_fixtureDef);
    _fixture->SetUserData(new GroundAreaFUD(0.3f, false, true, _id));
}

Grass::Grass(b2World* world, size_t id, int type, float x_init, float y_init, float angle_init, std::shared_ptr<Configuration> configuration) :
            _id(id), _type(type) {
    _setBodyDef(x_init, y_init, angle_init, configuration);

    _body = world->CreateBody(&_bodyDef);
    _setFixtureDef(configuration);

    _body->SetUserData(this);
}

Grass::~Grass(){
    _body->GetWorld()->DestroyBody(_body);
}