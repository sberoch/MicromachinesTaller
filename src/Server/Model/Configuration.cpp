#include <fstream>
#include "Configuration.h"
#include <iostream>

#define CONFIG_FILE "../json/configuration.json"

using json = nlohmann::json;

Configuration::Configuration() {
    std::ifstream i(CONFIG_FILE);
    json j; i >> j;

    json worldConfig = j["world"];
    _gravityX = worldConfig["gravityX"].get<float>();
    _gravityY = worldConfig["gravityY"].get<float>();
    _FPS = worldConfig["FPS"].get<float>();
    _velocityIterations = worldConfig["velocityIterations"].get<float>();
    _positionIterations = worldConfig["positionIterations"].get<float>();
}

float Configuration::getGravityX(){
    return _gravityX;
}

float Configuration::getGravityY(){
    return _gravityY;
}

float Configuration::getFPS(){
    return _FPS;
}

float Configuration::getVelocityIterations(){
    return _velocityIterations;
}

float Configuration::getPositionIterations(){
    return _positionIterations;
}

float Configuration::getCarWidth(){
    return _carHalfWidth;
}

float Configuration::getCarHeight(){
    return _carHalfHeight;
}

float Configuration::getTrackWidth(){
    return _trackHalfWidth;
}

float Configuration::getTrackHeight(){
    return _trackHalfHeight;
}

float Configuration::getRockHalfLen(){
    return _rockHalfLen;
}

float Configuration::getMudHalfLen(){
    return _mudHalfLen;
}

float Configuration::getHealthPowerUpHalfLen(){
    return _healthPowerUpHalfLen;
}