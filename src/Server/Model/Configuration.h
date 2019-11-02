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
    float _linearDamping;
    float _angularDamping;
    float _linearVelocityInit;
    float _angularVelocityInit;

    //Track
    float _trackHalfWidth;
    float _trackHalfHeight;
    float _trackFriction;
    float _trackDensity;
    float _trackRestitution;

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
    float getLinearDamping();
    float getAngularDamping();
    float getLinearVelocityInit();
    float getAngularVelocityInit();

    float getTrackWidth();
    float getTrackHeight();
    float getTrackDensity();
    float getTrackFriction();
    float getTrackRestitution();

    float getRockHalfLen();
    float getMudHalfLen();
    float getHealthPowerUpHalfLen();

};

#endif //MICROMACHINES_CONFIGURATION_H
