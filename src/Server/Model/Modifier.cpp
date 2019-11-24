#include "Modifier.h"

std::shared_ptr<Modifier> Modifier::makeModifier(std::shared_ptr<b2World> world, const size_t& type, const size_t& id, const float& x_init,
                                 const float& y_init, const float& angle, const std::shared_ptr<Configuration>& configuration){
    switch (type) {
        case TYPE_HEALTH_POWERUP :
            return std::shared_ptr<Modifier>(new HealthPowerup(world, type, id, x_init, y_init, angle, configuration));
        case TYPE_BOOST_POWERUP :
            return std::shared_ptr<Modifier>(new BoostPowerup(world, type, id, x_init, y_init, angle, configuration));
        case TYPE_ROCK :
            return std::shared_ptr<Modifier>(new Rock(world, type, id, x_init, y_init, angle, configuration));
        case TYPE_MUD :
            return std::shared_ptr<Modifier>(new Mud(world, type, id, x_init, y_init, angle, configuration));
        case TYPE_OIL :
            return std::shared_ptr<Modifier>(new Oil(world, type, id, x_init, y_init, angle, configuration));
    }

}

Modifier::Modifier(const std::shared_ptr<b2World>& world, size_t type, size_t id, float x_init, float y_init, float angle,
                   const std::shared_ptr<Configuration>& configuration) :
                   _type(type), _id(id), _x(x_init), _y(y_init), _angle(angle), _toDelete(false) {
    _setBodyDef(x_init, y_init, angle);
    _body = world->CreateBody(&_bodyDef);
}

void Modifier::_setBodyDef(float x_init, float y_init, float angle_init){
    _bodyDef.type = b2_staticBody;
    _bodyDef.position.Set(x_init, y_init);
    _bodyDef.angle = angle_init;
}

bool Modifier::toDelete(){
    return _toDelete;
}

void Modifier::markToDelete(){
    _toDelete = true;
}

size_t Modifier::getId(){
    return _id;
}

void Modifier::toDTO(ModifierDTO_t* modifierDTO){
    modifierDTO->id = _id;
    modifierDTO->x = _x;
    modifierDTO->y = _y;
    modifierDTO->angle = _angle;
    modifierDTO->newModifier = false;
    modifierDTO->active = !_toDelete;
}

////////////           HEALTHPU               ///////////

HealthPowerup::HealthPowerup(const std::shared_ptr<b2World>& world, size_t type, size_t id, float x_init, float y_init,
                             float angle, const std::shared_ptr<Configuration>& configuration) :
                             Modifier(world, type, id, x_init, y_init, angle, configuration),
                             hpFUD(new HealthPowerupFUD(_id, configuration->getHealthToIncrease())){
    _setFixtureDef(configuration);
    _body->SetUserData(this);
}

void HealthPowerup::_setFixtureDef(const std::shared_ptr<Configuration>& configuration) {
    b2PolygonShape shape;
    shape.SetAsBox(configuration->getHealthPowerUpHalfWidth(), configuration->getHealthPowerUpHalfHeight());
    _fixtureDef.shape = &shape;
    _fixtureDef.density = configuration->getHealthPowerUpDensity();
    _fixtureDef.friction = 0;
    _fixtureDef.restitution = 0;
    _fixtureDef.isSensor = true;

    _fixture = _body->CreateFixture(&_fixtureDef);
    _fixture->SetUserData(hpFUD.get());
}

HealthPowerup::~HealthPowerup() {
    _body->GetWorld()->DestroyBody(_body);
}

////////////           BOOSTPU               ///////////

BoostPowerup::BoostPowerup(const std::shared_ptr<b2World>& world, size_t type, size_t id, float x_init, float y_init,
                           float angle, const std::shared_ptr<Configuration>& configuration) :
                           Modifier(world, type, id, x_init, y_init, angle, configuration),
                           bpFUD(new BoostPowerupFUD(configuration->getBoostPowerUpActionTime(),
                                                        configuration->getBoostSpeedToIncrease(),
                                                        configuration->getBoostNewDrive(), _id)){
    _setBodyDef(x_init, y_init, angle);

    _setFixtureDef(configuration);
    _body->SetUserData(this);
}

void BoostPowerup::_setFixtureDef(const std::shared_ptr<Configuration> &configuration) {
    b2PolygonShape shape;
    shape.SetAsBox(configuration->getBoostPowerUpHalfWidth(), configuration->getBoostPowerUpHalfHeight());
    _fixtureDef.shape = &shape;
    _fixtureDef.density = configuration->getBoostPowerUpDensity();
    _fixtureDef.isSensor = true;

    _fixture = _body->CreateFixture(&_fixtureDef);
    _fixture->SetUserData(bpFUD.get());
}

BoostPowerup::~BoostPowerup() {
    _body->GetWorld()->DestroyBody(_body);
}

////////////           ROCK               ///////////

Rock::Rock(const std::shared_ptr<b2World>& world, size_t type, size_t id, float x_init, float y_init, float angle,
           const std::shared_ptr<Configuration>& configuration) :
           Modifier(world, type, id, x_init, y_init, angle, configuration),
           rFUD(new RockFUD(configuration->getRockVelToReduce(), configuration->getRockHealthToReduce(),
                         configuration->getRockDriveToReduce(), configuration->getRockTimeOfAction(), _id)){
    _setFixtureDef(configuration);
    _body->SetUserData(this);
}

void Rock::_setFixtureDef(const std::shared_ptr<Configuration> &configuration) {
    b2PolygonShape shape;
    shape.SetAsBox(configuration->getRockHalfWidth(), configuration->getRockHalfHeight());
    _fixtureDef.shape = &shape;
    _fixtureDef.density = configuration->getRockDensity();
    _fixtureDef.isSensor = false;
    _fixtureDef.restitution = 0.3f;

    _fixture = _body->CreateFixture(&_fixtureDef);
    _fixture->SetUserData(rFUD.get());
}

Rock::~Rock() {
    _body->GetWorld()->DestroyBody(_body);
}

////////////           MUD               ///////////

Mud::Mud(const std::shared_ptr<b2World>& world, size_t type, size_t id, float x_init, float y_init, float angle,
         const std::shared_ptr<Configuration>& configuration) :
        Modifier(world, type, id, x_init, y_init, angle, configuration),
        mFUD(new MudFUD(configuration->getMudTime(), _id)){

    _setFixtureDef(configuration);
    _body->SetUserData(this);
}

void Mud::_setFixtureDef(const std::shared_ptr<Configuration> &configuration) {
    b2PolygonShape shape;
    shape.SetAsBox(configuration->getMudHalfWidth(), configuration->getMudHalfHeight());
    _fixtureDef.shape = &shape;
    _fixtureDef.density = configuration->getMudDensity();
    _fixtureDef.isSensor = true;

    _fixture = _body->CreateFixture(&_fixtureDef);
    _fixture->SetUserData(mFUD.get());
}

Mud::~Mud() {
    _body->GetWorld()->DestroyBody(_body);
}

////////////           OIL               ///////////

Oil::Oil(const std::shared_ptr<b2World>& world, size_t type, size_t id, float x_init, float y_init, float angle,
         const std::shared_ptr<Configuration>& configuration) :
        Modifier(world, type, id, x_init, y_init, angle, configuration),
        oFUD(new OilFUD(configuration->getOilDamping(), configuration->getOilTime(), _id)){
    _setFixtureDef(configuration);
    _body->SetUserData(this);
}

void Oil::_setFixtureDef(const std::shared_ptr<Configuration> &configuration) {
    b2PolygonShape shape;
    shape.SetAsBox(configuration->getOilHalfWidth(), configuration->getOilHalfHeight());
    _fixtureDef.shape = &shape;
    _fixtureDef.density = configuration->getOilDensity();
    _fixtureDef.isSensor = true;

    _fixture = _body->CreateFixture(&_fixtureDef);
    _fixture->SetUserData(oFUD.get());
}

Oil::~Oil() {
    _body->GetWorld()->DestroyBody(_body);
}