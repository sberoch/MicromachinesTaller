#ifndef MICROMACHINES_CONFIGURATION_H
#define MICROMACHINES_CONFIGURATION_H

#include "../json/json.hpp"

//Class to get configuration options in json file
class Configuration {
private:
    //World
    float _gravityX;
    float _gravityY;
    float _FPS;
    float _velocityIterations;
    float _positionIterations;

    //Car
    float _carHalfWidth;
    float _carHalfHeight;
    float _maxHealth;
    float _maxForwardVelocity;
    float _maxBackwardsVelocity;

    //Track
    float _trackHalfWidth;
    float _trackHalfHeight;
    float _trackFriction;

    //Grass
    float _grassHalfWidth;
    float _grassHalfHeight;
    float _grassFriction;

    //Modifiers
    float _rockHalfLen;
    float _mudHalfLen;
    float _healthPowerUpHalfLen;

public:
    Configuration();
    float getGravityX();
    float getGravityY();
    float getFPS();
    float getVelocityIterations();
    float getPositionIterations();
    float getCarWidth();
    float getCarHeight();
    float getTrackWidth();
    float getTrackHeight();
    float getRockHalfLen();
    float getMudHalfLen();
    float getHealthPowerUpHalfLen();
    ~Configuration();
};

#endif //MICROMACHINES_CONFIGURATION_H
