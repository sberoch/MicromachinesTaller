#ifndef MICROMACHINES_TRACK_H
#define MICROMACHINES_TRACK_H

#include <string>
#include <Box2D/Box2D.h>

class Track {
private:
    int _type;
    float _x_size;
    float _y_size;
    float _friction;
    float _density;
    float _restitution;

    b2BodyDef _body_def;
    b2FixtureDef _fixture_def;
    b2Body* _body;

    void _setBodyDef();
    void _setFixtureDef();

public:
    Track(std::string config_filename, b2Body* body);
    ~Track();
};

#endif //MICROMACHINES_TRACK_H
