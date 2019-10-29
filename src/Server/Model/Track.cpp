#include "../json/json.hpp"
#include <fstream>
#include "Track.h"

using json = nlohmann::json;

void Track::_setBodyDef(){

}

void Track::_setFixtureDef(){
    b2PolygonShape floor_shape;
    floor_shape.SetAsBox(_x_size, _y_size);
    b2FixtureDef floor_fixture_def;
    floor_fixture_def.density = _density;
    floor_fixture_def.friction = _friction;
    floor_fixture_def.restitution = _restitution;
    floor_fixture_def.shape = &floor_shape;
}

Track::Track(std::string config_filename, b2Body* body){
    std::ifstream i(config_filename);
    json j; i >> j;

    json tracks = j["track_config"];
    _x_size = j["x_size"].get<float>();
    _y_size = j["y_size"].get<float>();
    _density = j["density"].get<float>();
    _friction = j["friction"].get<float>();
    _restitution = j["restitution"].get<float>();

    _body = body;
    _body->CreateFixture(&_fixture_def);
}