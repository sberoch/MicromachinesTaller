#ifndef MICROMACHINES_MODIFIER_H
#define MICROMACHINES_MODIFIER_H

#include <Box2D/Box2D.h>
#include <iostream>
#include "Configuration.h"
#include "FixtureUserData.h"

class Modifier {
protected:
    size_t _type, _id;
    b2BodyDef _bodyDef;
    b2Body* _body;
    b2FixtureDef _fixtureDef;
    b2Fixture* _fixture;
    bool _toDelete;

    Modifier(b2World* world, size_t type, size_t id, float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration)
             : _type(type), _id(id), _toDelete(false) {
        _setBodyDef(x_init, y_init, angle);
        _body = world->CreateBody(&_bodyDef);
    }

public:
    virtual void _setBodyDef(float x_init, float y_init, float angle_init){
        _bodyDef.type = b2_staticBody;
        _bodyDef.position.Set(x_init, y_init);
        _bodyDef.angle = angle_init;
    }

    virtual void _setFixtureDef(std::shared_ptr<Configuration> configuration) = 0;

    virtual bool toDelete(){
        return _toDelete;
    }

    virtual void markToDelete(){
        _toDelete = true;
    }

    virtual size_t getId(){
        return _id;
    }

public:
    virtual ~Modifier(){}
};

class HealthPowerup : public Modifier{
private:
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
                 Modifier(world, type, id, x_init, y_init, angle, configuration) {
        _setFixtureDef(configuration);

        _body->SetUserData(this);
    }

    ~HealthPowerup(){
        _body->GetWorld()->DestroyBody(_body);
    }
};

class BoostPowerup : public Modifier{
private:
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
            Modifier(world, type, id, x_init, y_init, angle, configuration) {
        _setBodyDef(x_init, y_init, angle);

        _setFixtureDef(configuration);
        _body->SetUserData(this);
    }

    ~BoostPowerup(){
        _body->GetWorld()->DestroyBody(_body);
    }
};

class Rock : public Modifier{
private:
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
            Modifier(world, type, id, x_init, y_init, angle, configuration) {
        _setFixtureDef(configuration);
        _body->SetUserData(this);
    }

    ~Rock(){
        _body->GetWorld()->DestroyBody(_body);
    }
};

class Mud : public Modifier{
private:
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
            Modifier(world, type, id, x_init, y_init, angle, configuration) {
        _setFixtureDef(configuration);
        _body->SetUserData(this);
    }

    ~Mud(){
        _body->GetWorld()->DestroyBody(_body);
    }
};

class Oil : public Modifier{
private:
    void _setFixtureDef(std::shared_ptr<Configuration> configuration){
        b2PolygonShape shape;
        shape.SetAsBox(configuration->getOilHalfWidth(), configuration->getOilHalfHeight());
        _fixtureDef.shape = &shape;
        _fixtureDef.density = configuration->getOilDensity();
        _fixtureDef.isSensor = true;

        _fixture = _body->CreateFixture(&_fixtureDef);
        _fixture->SetUserData(new OilFUD(configuration->getOilDamping(), configuration->getOilTime(), _id));
    }

public:
    Oil(b2World* world, size_t type, size_t id, float x_init, float y_init, float angle, std::shared_ptr<Configuration> configuration) :
            Modifier(world, type, id, x_init, y_init, angle, configuration) {
        _setFixtureDef(configuration);
        _body->SetUserData(this);
    }

    ~Oil(){
        _body->GetWorld()->DestroyBody(_body);
    }
};

#endif //MICROMACHINES_MODIFIER_H
