#include <fstream>
#include "Configuration.h"
#include <iostream>

#define CONFIG_FILE "/home/miki_mustard/Desktop/Facultad/Taller/clientmm/MicromachinesTaller/src/Server/json/configuration.json"

using json = nlohmann::json;

Configuration::Configuration() {
    std::ifstream i(CONFIG_FILE);
    json j; i >> j;

    json worldConfig = j["world_configuration"];
    _gravityX = worldConfig["gravityX"].get<float>();
    _gravityY = worldConfig["gravityY"].get<float>();
    _FPS = worldConfig["FPS"].get<float>();
    _velocityIterations = worldConfig["velocityIterations"].get<float>();
    _positionIterations = worldConfig["positionIterations"].get<float>();

    json carConfig = j["car_configuration"];
    _carHalfWidth = carConfig["carHalfWidth"].get<float>();
    _carHalfHeight = carConfig["carHalfHeight"].get<float>();
    _maxHealth = carConfig["maxHealth"].get<float>();
    _maxForwardVelocity = carConfig["maxForwardVelocity"].get<float>();
    _maxBackwardsVelocity = carConfig["maxBackwardsVelocity"].get<float>();
    _linearDamping = carConfig["linearDamping"].get<float>();
    _angularDamping = carConfig["angularDamping"].get<float>();
    _linearVelocityInit = carConfig["linearVelocityInit"].get<float>();
    _angularVelocityInit = carConfig["angularVelocityInit"].get<float>();

    json trackConfig = j["track_configuration"];
    _trackHalfWidth = trackConfig["halfWidth"].get<float>();
    _trackHalfHeight = trackConfig["halfHeight"].get<float>();
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

float Configuration::getLinearDamping(){
    return _linearDamping;
}

float Configuration::getAngularDamping(){
    return _angularDamping;
}

float Configuration::getLinearVelocityInit(){
    return _linearVelocityInit;
}

float Configuration::getAngularVelocityInit(){
    return _angularVelocityInit;
}

float Configuration::getTrackWidth(){
    return _trackHalfWidth;
}

float Configuration::getTrackHeight(){
    return _trackHalfHeight;
}

float Configuration::getTrackDensity(){
    return _trackDensity;
}

float Configuration::getTrackFriction(){
    return _trackFriction;
}

float Configuration::getTrackRestitution(){
    return _trackRestitution;
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