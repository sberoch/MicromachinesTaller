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
    float _desiredTorque;
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
    float _grassDensity;
    float _grassRestitution;

    //Modifiers
    float _healthPowerUpHalfWidth;
    float _healthPowerUpHalfHeight;
    float _healthPowerUpDensity;

    float _boostPowerUpHalfWidth;
    float _boostPowerUpHalfHeight;
    float _boostPowerUpDensity;

    float _rockHalfWidth;
    float _rockHalfHeight;
    float _rockDensity;
    float _velToReduce;
    float _healthToReduce;

    float _mudHalfWidth;
    float _mudHalfHeight;
    float _mudDensity;
    float _mudTime;

    float _oilHalfWidth;
    float _oilHalfHeight;
    float _oilDensity;
    float _newLinearDamping;
    float _newAngularDamping;
    float _oilTime;

public:
    Configuration();
    float getGravityX();
    float getGravityY();
    float getFPS();
    float getVelocityIterations();
    float getPositionIterations();

    float getCarWidth();
    float getCarHeight();
    float getMaxHealth();
    float getMaxForwardVelocity();
    float getMaxBackwardsVelocity();
    float getDesiredTorque();
    float getLinearDamping();
    float getAngularDamping();
    float getLinearVelocityInit();
    float getAngularVelocityInit();

    float getTrackWidth();
    float getTrackHeight();
    float getTrackDensity();
    float getTrackFriction();
    float getTrackRestitution();

    float getGrassWidth();
    float getGrassHeight();
    float getGrassDensity();
    float getGrassFriction();
    float getGrassRestitution();

    float getHealthPowerUpHalfWidth();
    float getHealthPowerUpHalfHeight();
    float getHealthPowerUpDensity();

    float getBoostPowerUpHalfWidth();
    float getBoostPowerUpHalfHeight();
    float getBoostPowerUpDensity();

    float getRockHalfWidth();
    float getRockHalfHeight();
    float getRockDensity();
    float getRockVelToReduce();
    float getRockHealthToReduce();

    float getMudHalfWidth();
    float getMudHalfHeight();
    float getMudDensity();
    float getMudTime();

    float getOilHalfWidth();
    float getOilHalfHeight();
    float getOilDensity();
    float getOilTime();
    float getOilLinearDamping();
    float getOilAngularDamping();

};

#endif //MICROMACHINES_CONFIGURATION_H
