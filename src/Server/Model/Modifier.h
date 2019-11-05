#ifndef MICROMACHINES_MODIFIER_H
#define MICROMACHINES_MODIFIER_H

#include <Box2D/Box2D.h>
#include <iostream>
#include "Configuration.h"
#include "FixtureUserData.h"

class Modifier {
private:
    size_t _type, _id;
    b2BodyDef _bodyDef;
    b2Body _body;
    b2FixtureDef _fixtureDef;
    b2Fixture _fixture;

    void _setBodyDef(float x_init, float y_init, float angle_init, std::shared_ptr<Configuration> configuration);
    void _setFixtureDef(std::shared_ptr<Configuration> configuration);

public:
    Modifier(b2World* world, size_t type, size_t id, float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration);
    ~Modifier();
};

class HealthPowerup {
private:
    size_t _type, _id;
    b2BodyDef _bodyDef;
    b2Body* _body;
    b2FixtureDef _fixtureDef;
    b2Fixture* _fixture;

    void _setBodyDef(float x_init, float y_init, float angle_init){
        _bodyDef.type = b2_staticBody;
        _bodyDef.position.Set(x_init, y_init);
        _bodyDef.angle = angle_init;
    }

    void _setFixtureDef(std::shared_ptr<Configuration> configuration){
        b2PolygonShape shape;
        shape.SetAsBox(configuration->getHealthPowerUpHalfWidth(), configuration->getHealthPowerUpHalfHeight());
        _fixtureDef.shape = &shape;
        _fixtureDef.density = configuration->getHealthPowerUpDensity();
        _fixtureDef.friction = 0;
        _fixtureDef.restitution = 0;
        _fixtureDef.isSensor = true;

        _fixture = _body->CreateFixture(&_fixtureDef);
        _fixture->SetUserData(new HealthPowerupFUD(_id));
    }

public:
    HealthPowerup(b2World* world, size_t type, size_t id, float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration) :
                 _id(id), _type(type) {
        _setBodyDef(x_init, y_init, angle);

        _body = world->CreateBody(&_bodyDef);
        _setFixtureDef(configuration);

        _body->SetUserData(this);
    }

    ~HealthPowerup(){
        _body->GetWorld()->DestroyBody(_body);
    }
};

class BoostPowerup{
private:
    size_t _type, _id;
    b2BodyDef _bodyDef;
    b2Body* _body;
    b2FixtureDef _fixtureDef;
    b2Fixture* _fixture;

    void _setBodyDef(float x_init, float y_init, float angle_init){
        _bodyDef.type = b2_staticBody;
        _bodyDef.position.Set(x_init, y_init);
        _bodyDef.angle = angle_init;
    }

    void _setFixtureDef(std::shared_ptr<Configuration> configuration){
        b2PolygonShape shape;
        shape.SetAsBox(configuration->getHealthPowerUpHalfWidth(), configuration->getHealthPowerUpHalfHeight());
        _fixtureDef.shape = &shape;
        _fixtureDef.density = configuration->getHealthPowerUpDensity();
        _fixtureDef.isSensor = true;

        _fixture = _body->CreateFixture(&_fixtureDef);
        _fixture->SetUserData(new BoostPowerupFUD(10, _id));
    }

public:
    BoostPowerup(b2World* world, size_t type, size_t id, float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration) :
            _id(id), _type(type) {
        _setBodyDef(x_init, y_init, angle);

        _body = world->CreateBody(&_bodyDef);
        _setFixtureDef(configuration);
        _body->SetUserData(this);
    }

    ~BoostPowerup(){
        _body->GetWorld()->DestroyBody(_body);
    }
};

class Rock{
private:
    size_t _type, _id;
    b2BodyDef _bodyDef;
    b2Body* _body;
    b2FixtureDef _fixtureDef;
    b2Fixture* _fixture;

    void _setBodyDef(float x_init, float y_init, float angle_init){
        _bodyDef.type = b2_staticBody;
        _bodyDef.position.Set(x_init, y_init);
        _bodyDef.angle = angle_init;
    }

    void _setFixtureDef(std::shared_ptr<Configuration> configuration){
        b2PolygonShape shape;
        shape.SetAsBox(configuration->getRockHalfWidth(), configuration->getRockHalfHeight());
        _fixtureDef.shape = &shape;
        _fixtureDef.density = configuration->getRockDensity();
        _fixtureDef.isSensor = true;

        _fixture = _body->CreateFixture(&_fixtureDef);
        _fixture->SetUserData(new RockFUD(configuration->getRockVelToReduce(), configuration->getRockHealthToReduce(), _id));
    }

public:
    Rock(b2World* world, size_t type, size_t id, float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration) :
            _id(id), _type(type) {
        _setBodyDef(x_init, y_init, angle);

        _body = world->CreateBody(&_bodyDef);
        _setFixtureDef(configuration);
        _body->SetUserData(this);
    }

    ~Rock(){
        _body->GetWorld()->DestroyBody(_body);
    }
};

class Mud{
private:
    size_t _type, _id;
    b2BodyDef _bodyDef;
    b2Body* _body;
    b2FixtureDef _fixtureDef;
    b2Fixture* _fixture;

    void _setBodyDef(float x_init, float y_init, float angle_init){
        _bodyDef.type = b2_staticBody;
        _bodyDef.position.Set(x_init, y_init);
        _bodyDef.angle = angle_init;
    }

    void _setFixtureDef(std::shared_ptr<Configuration> configuration){
        b2PolygonShape shape;
        shape.SetAsBox(configuration->getMudHalfWidth(), configuration->getMudHalfHeight());
        _fixtureDef.shape = &shape;
        _fixtureDef.density = configuration->getMudDensity();
        _fixtureDef.isSensor = true;

        _fixture = _body->CreateFixture(&_fixtureDef);
        _fixture->SetUserData(new MudFUD(configuration->getMudTime(), _id));
    }

public:
    Mud(b2World* world, size_t type, size_t id, float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration) :
            _id(id), _type(type) {
        _setBodyDef(x_init, y_init, angle);

        _body = world->CreateBody(&_bodyDef);
        _setFixtureDef(configuration);
        _body->SetUserData(this);
    }

    ~Mud(){
        _body->GetWorld()->DestroyBody(_body);
    }
};

class Oil{
private:
    size_t _type, _id;
    b2BodyDef _bodyDef;
    b2Body* _body;
    b2FixtureDef _fixtureDef;
    b2Fixture* _fixture;

    void _setBodyDef(float x_init, float y_init, float angle_init){
        _bodyDef.type = b2_staticBody;
        _bodyDef.position.Set(x_init, y_init);
        _bodyDef.angle = angle_init;
    }

    void _setFixtureDef(std::shared_ptr<Configuration> configuration){
        b2PolygonShape shape;
        shape.SetAsBox(configuration->getOilHalfWidth(), configuration->getOilHalfHeight());
        _fixtureDef.shape = &shape;
        _fixtureDef.density = configuration->getOilDensity();
        _fixtureDef.isSensor = true;

        _fixture = _body->CreateFixture(&_fixtureDef);
        _fixture->SetUserData(new OilFUD(configuration->getOilLinearDamping(), configuration->getOilAngularDamping(), configuration->getOilTime(), _id));
    }

public:
    Oil(b2World* world, size_t type, size_t id, float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration) :
            _id(id), _type(type) {
        _setBodyDef(x_init, y_init, angle);

        _body = world->CreateBody(&_bodyDef);
        _setFixtureDef(configuration);
        _body->SetUserData(this);
    }

    ~Oil(){
        _body->GetWorld()->DestroyBody(_body);
    }
};

#endif //MICROMACHINES_MODIFIER_H
