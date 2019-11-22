#ifndef MICROMACHINES_TRACK_H
#define MICROMACHINES_TRACK_H

#include <string>
#include <Box2D/Box2D.h>
#include "Configuration.h"
#include "../mods/DTOs.h"

class Track {
private:
    int _type;
    size_t _id;

    bool _start;
    bool _finish;

    b2BodyDef _bodyDef;
    b2FixtureDef _fixtureDef;
    b2Fixture* _fixture;
    b2Body* _body;

    void _setBodyDef(float x_init, float y_init, float angle_init, std::shared_ptr<Configuration> configuration);
    void _setFixtureDef(std::shared_ptr<Configuration> configuration);

    bool _isBetweenLimits(const float& pos, const char& xOrY);

public:
    Track(b2World* world, size_t id, int type, float x_init, float y_init, float angle_init, std::shared_ptr<Configuration> configuration);

    void setAsStart();
    void setAsFinish();

    bool isStart();
    bool isFinish();

    float getDistance(const float& x, const float& y);

    const float x();
    const float y();
    const float angle();
    const int type();

    bool equals(Track* other);

    void toDTO(TrackDTO_t* trackDTO);

    ~Track() = default;
};

#endif //MICROMACHINES_TRACK_H
