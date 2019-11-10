#ifndef MICROMACHINES_TRACK_H
#define MICROMACHINES_TRACK_H

#include <string>
#include <Box2D/Box2D.h>
#include "Configuration.h"

class Track {
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
    Track(b2World* world, size_t id, int type, float x_init, float y_init, float angle_init, std::shared_ptr<Configuration> configuration);

    const float x();
    const float y();
    const float angle();
    const int type();

    bool equals(Track* other);

    ~Track();
};

#endif //MICROMACHINES_TRACK_H
