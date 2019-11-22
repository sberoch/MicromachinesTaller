#ifndef MICROMACHINES_GRASS_H
#define MICROMACHINES_GRASS_H

#include <Box2D/Box2D.h>
#include "Configuration.h"

class Grass {
private:
    int _type;
    size_t _id;

    b2BodyDef _bodyDef;
    b2FixtureDef _fixtureDef;
    b2Fixture* _fixture;
    b2Body* _body;

    void _setBodyDef(float x_init, float y_init, float angle_init, std::shared_ptr<Configuration> configuration);
    void _setFixtureDef(std::shared_ptr<Configuration> configuration);

public:
    Grass(b2World* world, size_t id, int type, float x_init, float y_init, float angle_init, std::shared_ptr<Configuration> configuration);
    ~Grass() = default;
};

#endif //MICROMACHINES_GRASS_H
