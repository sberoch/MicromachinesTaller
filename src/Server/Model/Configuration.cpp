#include <fstream>
#include "Configuration.h"
#include <iostream>

#define CONFIG_FILE MISC_DIR + std::string("configuration.json")

using json = nlohmann::json;

Configuration::Configuration() {
    std::ifstream i(CONFIG_FILE);
    json j;
    i >> j;

    json worldConfig = j["world_configuration"];
    _gravityX = worldConfig["gravityX"].get<float>();
    _gravityY = worldConfig["gravityY"].get<float>();
    _FPS = worldConfig["FPS"].get<float>();
    _velocityIterations = worldConfig["velocityIterations"].get<float>();
    _positionIterations = worldConfig["positionIterations"].get<float>();
    _maxDistToTrack = worldConfig["maxDistToTrack"].get<float>();
    _modifiersCreationFrequency = worldConfig["modifiersCreationFrequency"].get<int>();
    _mapToUse = worldConfig["mapToUse"].get<std::string>();
    _maxLaps = worldConfig["maxLaps"].get<int>();

    json carConfig = j["car_configuration"];
    _carHalfWidth = carConfig["carHalfWidth"].get<float>();
    _carHalfHeight = carConfig["carHalfHeight"].get<float>();
    _maxHealth = carConfig["maxHealth"].get<float>();
    _maxForwardSpeed = carConfig["maxForwardSpeed"].get<float>();
    _maxForwardDrive = carConfig["maxForwardDrive"].get<float>();
    _maxBackwardsSpeed = carConfig["maxBackwardsSpeed"].get<float>();
    _maxBackwardDrive = carConfig["maxForwardDrive"].get<float>();
    _maxForwardSpeedOnGrass = carConfig["maxForwardSpeedOnGrass"].get<float>();
    _maxForwardDriveOnGrass = carConfig["maxForwardDriveOnGrass"].get<float>();
    _maxBackwardSpeedOnGrass = carConfig["maxBackwardSpeedOnGrass"].get<float>();
    _maxBackwardDriveOnGrass = carConfig["maxBackwardDriveOnGrass"].get<float>();
    _currentForwardSpeed = carConfig["currentForwardSpeed"].get<float>();
    _currentForwardDrive = carConfig["currentForwardDrive"].get<float>();
    _currentBackwardSpeed = carConfig["currentBackwardSpeed"].get<float>();
    _currentBackwardDrive = carConfig["currentBackwardDrive"].get<float>();
    _maxLateralImpulse = carConfig["maxLateralImpulse"].get<float>();
    _maxDriveForce = carConfig["maxDriveForce"].get<float>();
    _angularImpulse = carConfig["angularImpulse"].get<float>();
    _desiredTorque = carConfig["desiredTorque"].get<float>();
    _linearDamping = carConfig["linearDamping"].get<float>();
    _angularDamping = carConfig["angularDamping"].get<float>();
    _linearVelocityInit = carConfig["linearVelocityInit"].get<float>();
    _angularVelocityInit = carConfig["angularVelocityInit"].get<float>();
    _carDensity = carConfig["density"].get<float>();
    _carFriction = carConfig["friction"].get<float>();

    json trackConfig = j["track_configuration"];
    _trackHalfWidth = trackConfig["halfWidth"].get<float>();
    _trackHalfHeight = trackConfig["halfHeight"].get<float>();
    _trackDensity = trackConfig["density"].get<float>();
    _trackFriction = trackConfig["friction"].get<float>();
    _trackRestitution = trackConfig["restitution"].get<float>();

    json grassConfig = j["grass_configuration"];
    _grassHalfWidth = grassConfig["halfWidth"].get<float>();
    _grassHalfHeight = grassConfig["halfHeight"].get<float>();
    _grassDensity = grassConfig["density"].get<float>();
    _grassFriction = grassConfig["friction"].get<float>();
    _grassRestitution = grassConfig["restitution"].get<float>();

    json healthPUConfig = j["healthPowerupConfiguration"];
    _healthPowerUpHalfWidth = healthPUConfig["halfWidth"].get<float>();
    _healthPowerUpHalfHeight = healthPUConfig["halfHeight"].get<float>();
    _healthPowerUpDensity = healthPUConfig["density"].get<float>();
    _healthToIncrease = healthPUConfig["healthToIncrease"].get<int>();

    json boostPUConfig = j["boostPowerupConfiguration"];
    _boostPowerUpHalfWidth = boostPUConfig["halfWidth"].get<float>();
    _boostPowerUpHalfHeight = boostPUConfig["halfHeight"].get<float>();
    _boostPowerUpDensity = boostPUConfig["density"].get<float>();
    _boostPowerUpActionTime = boostPUConfig["actionTime"].get<float>();
    _boostSpeedToIncrease = boostPUConfig["speedToIncrease"].get<float>();
    _boostNewDrive = boostPUConfig["newDrive"].get<float>();

    json mudConfig = j["mudConfiguration"];
    _mudHalfWidth = mudConfig["halfWidth"].get<float>();
    _mudHalfHeight = mudConfig["halfHeight"].get<float>();
    _mudDensity = mudConfig["density"].get<float>();
    _mudTime = mudConfig["time"].get<float>();

    json rockConfig = j["rockConfiguration"];
    _rockHalfWidth = rockConfig["halfWidth"].get<float>();
    _rockHalfHeight = rockConfig["halfHeight"].get<float>();
    _rockDensity = rockConfig["density"].get<float>();
    _rockTimeOfAction = rockConfig["timeOfAction"].get<int>();
    _velToReduce = rockConfig["velToReduce"].get<float>();
    _rockDriveToReduce = rockConfig["driveToReduce"].get<int>();
    _healthToReduce = rockConfig["healthToReduce"].get<float>();

    json oilConfig = j["oilConfiguration"];
    _oilHalfWidth = oilConfig["halfWidth"].get<float>();
    _oilHalfHeight = oilConfig["halfHeight"].get<float>();
    _oilDensity = oilConfig["density"].get<float>();
    _oilTime = oilConfig["time"].get<float>();
    _newDamping = oilConfig["damping"].get<float>();
}

///////////////   GENERAL   /////////////////
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

float Configuration::getMaxDistToTrack(){
    return _maxDistToTrack;
}

int Configuration::getModifiersCreationFrequency(){
    return _modifiersCreationFrequency;
}

std::string Configuration::getMapToUse() {
    return _mapToUse;
}

int Configuration::getMaxLaps() {
    return _maxLaps;
}

///////////////   CAR   /////////////////
float Configuration::getCarWidth(){
    return _carHalfWidth;
}

float Configuration::getCarHeight(){
    return _carHalfHeight;
}

float Configuration::getCarMaxHealth(){
    return _maxHealth;
}

float Configuration::getMaxForwardSpeed(){
    return _maxForwardSpeed;
}

float Configuration::getMaxForwardDrive(){
    return _maxForwardDrive;
}

float Configuration::getMaxBackwardsSpeed(){
    return _maxBackwardsSpeed;
}

float Configuration::getMaxBackwardDrive(){
    return _maxBackwardDrive;
}

float Configuration::getMaxForwardSpeedOnGrass(){
    return _maxForwardSpeedOnGrass;
}

float Configuration::getMaxForwardDriveOnGrass(){
    return _maxForwardDriveOnGrass;
}

float Configuration::getMaxBackwardSpeedOnGrass(){
    return _maxBackwardSpeedOnGrass;
}

float Configuration::getMaxBackwardDriveOnGrass(){
    return _maxBackwardDriveOnGrass;
}

float Configuration::getCurrentForwardSpeed(){
    return _currentForwardSpeed;
}

float Configuration::getCurrentForwardDrive(){
    return _currentForwardDrive;
}

float Configuration::getCurrentBackwardSpeed(){
    return _currentBackwardSpeed;
}

float Configuration::getCurrentBackwardDrive(){
    return _currentBackwardDrive;
}

float Configuration::getCarMaxLateralImpulse(){
    return _maxLateralImpulse;
}

float Configuration::getCarAngularImpulse(){
    return _angularImpulse;
}

float Configuration::getCarDesiredTorque(){
    return _desiredTorque;
}

float Configuration::getCarDensity(){
    return _carDensity;
}

float Configuration::getCarFriction(){
    return _carFriction;
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

///////////////   TRACK   /////////////////
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

///////////////   GRASS   /////////////////
float Configuration::getGrassWidth(){
    return _grassHalfWidth;
}

float Configuration::getGrassHeight(){
    return _grassHalfHeight;
}

float Configuration::getGrassDensity(){
    return _grassDensity;
}

float Configuration::getGrassFriction(){
    return _grassFriction;
}

float Configuration::getGrassRestitution(){
    return _grassRestitution;
}

///////////////   HEALTHPU   /////////////////
float Configuration::getHealthPowerUpHalfWidth(){
    return _healthPowerUpHalfWidth;
}

float Configuration::getHealthPowerUpHalfHeight(){
    return _healthPowerUpHalfHeight;
}

float Configuration::getHealthPowerUpDensity(){
    return _healthPowerUpDensity;
}

int Configuration::getHealthToIncrease() {
    return _healthToIncrease;
}


///////////////   BOOST   /////////////////
float Configuration::getBoostPowerUpHalfWidth(){
    return _boostPowerUpHalfWidth;
}

float Configuration::getBoostPowerUpHalfHeight(){
    return _boostPowerUpHalfHeight;
}

float Configuration::getBoostPowerUpDensity(){
    return _boostPowerUpDensity;
}

float Configuration::getBoostPowerUpActionTime() {
    return _boostPowerUpActionTime;
}

float Configuration::getBoostSpeedToIncrease() {
    return _boostSpeedToIncrease;
}

float Configuration::getBoostNewDrive() {
    return _boostNewDrive;
}

///////////////   ROCK   /////////////////
float Configuration::getRockHalfWidth(){
    return _rockHalfWidth;
}

float Configuration::getRockHalfHeight(){
    return _rockHalfHeight;
}

float Configuration::getRockDensity(){
    return _rockDensity;
}

float Configuration::getRockVelToReduce(){
    return _velToReduce;
}

float Configuration::getRockHealthToReduce(){
    return _healthToReduce;
}

int Configuration::getRockTimeOfAction() {
    return _rockTimeOfAction;
}

int Configuration::getRockDriveToReduce() {
    return _rockDriveToReduce;
}

///////////////   MUD   /////////////////
float Configuration::getMudHalfWidth(){
    return _mudHalfWidth;
}

float Configuration::getMudHalfHeight(){
    return _mudHalfHeight;
}

float Configuration::getMudDensity(){
    return _mudDensity;
}

float Configuration::getMudTime(){
    return _mudTime;
}

///////////////   OIL   /////////////////
float Configuration::getOilHalfWidth(){
    return _oilHalfWidth;
}

float Configuration::getOilHalfHeight(){
    return _oilHalfHeight;
}

float Configuration::getOilDensity(){
    return _oilDensity;
}

float Configuration::getOilTime(){
    return _oilTime;
}

float Configuration::getOilDamping(){
    return _newDamping;
}