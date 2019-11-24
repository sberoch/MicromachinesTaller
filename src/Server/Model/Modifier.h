#ifndef MICROMACHINES_MODIFIER_H
#define MICROMACHINES_MODIFIER_H

#include <Box2D/Box2D.h>
#include <iostream>
#include "Configuration.h"
#include "FixtureUserData.h"
#include "../../Common/Constants.h"
#include "../mods/DTOs.h"

class Modifier {
protected:
    size_t _type, _id;
    float _x, _y, _angle;
    b2BodyDef _bodyDef;
    b2Body* _body;
    b2FixtureDef _fixtureDef;
    b2Fixture* _fixture;
    bool _toDelete;

    Modifier(const std::shared_ptr<b2World>& world, size_t type, size_t id, float x_init, float y_init, float angle, const std::shared_ptr<Configuration>& configuration);

public:
    virtual void _setBodyDef(float x_init, float y_init, float angle_init);
    virtual void _setFixtureDef(const std::shared_ptr<Configuration>& configuration) = 0;
    virtual bool toDelete();
    virtual void markToDelete();
    virtual size_t getId();
    virtual void toDTO(ModifierDTO_t* modifierDTO);

    static std::shared_ptr<Modifier> makeModifier(std::shared_ptr<b2World> world, const size_t& type, const size_t& id, const float& x_init,
                                  const float& y_init, const float& angle, const std::shared_ptr<Configuration>& configuration);

    virtual ~Modifier() = default;
};

class HealthPowerup : public Modifier{
private:
    std::shared_ptr<HealthPowerupFUD> hpFUD;
    void _setFixtureDef(const std::shared_ptr<Configuration>& configuration) override;

public:
    HealthPowerup(const std::shared_ptr<b2World>& world, size_t type, size_t id, float x_init,
            float y_init, float angle, const std::shared_ptr<Configuration>& configuration);

    ~HealthPowerup() override;
};

class BoostPowerup : public Modifier{
private:
    std::shared_ptr<BoostPowerupFUD> bpFUD;
    void _setFixtureDef(const std::shared_ptr<Configuration>& configuration) override;

public:
    BoostPowerup(const std::shared_ptr<b2World>& world, size_t type, size_t id, float x_init,
            float y_init, float angle, const std::shared_ptr<Configuration>& configuration);

    ~BoostPowerup() override;
};

class Rock : public Modifier{
private:
    std::shared_ptr<RockFUD> rFUD;
    void _setFixtureDef(const std::shared_ptr<Configuration>& configuration) override;

public:
    Rock(const std::shared_ptr<b2World>& world, size_t type, size_t id, float x_init,
            float y_init, float angle, const std::shared_ptr<Configuration>& configuration);

    ~Rock() override;
};

class Mud : public Modifier{
private:
    std::shared_ptr<MudFUD> mFUD;
    void _setFixtureDef(const std::shared_ptr<Configuration>& configuration) override;

public:
    Mud(const std::shared_ptr<b2World>& world, size_t type, size_t id, float x_init,
            float y_init, float angle, const std::shared_ptr<Configuration>& configuration);

    ~Mud() override;
};

class Oil : public Modifier{
private:
    std::shared_ptr<OilFUD> oFUD;
    void _setFixtureDef(const std::shared_ptr<Configuration>& configuration) override;

public:
    Oil(const std::shared_ptr<b2World>& world, size_t type, size_t id, float x_init,
            float y_init, float angle, const std::shared_ptr<Configuration>& configuration);

    ~Oil() override;
};

#endif //MICROMACHINES_MODIFIER_H
