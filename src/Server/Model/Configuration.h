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
    float _maxDistToTrack;
    int _modifiersCreationFrequency;
    std::string _mapToUse;
    int _maxLaps;

    //Car
    float _carHalfWidth;
    float _carHalfHeight;
    float _maxHealth;
    float _maxForwardSpeed;
    float _maxForwardDrive;
    float _maxBackwardsSpeed;
    float _maxBackwardDrive;
    float _maxForwardSpeedOnGrass;
    float _maxForwardDriveOnGrass;
    float _maxBackwardSpeedOnGrass;
    float _maxBackwardDriveOnGrass;
    float _currentForwardSpeed;
    float _currentForwardDrive;
    float _currentBackwardSpeed;
    float _currentBackwardDrive;
    float _maxLateralImpulse;
    float _maxDriveForce;
    float _angularImpulse;
    float _desiredTorque;
    float _linearDamping;
    float _angularDamping;
    float _linearVelocityInit;
    float _angularVelocityInit;
    float _carDensity;
    float _carFriction;

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
    float _healthToIncrease;

    float _boostPowerUpHalfWidth;
    float _boostPowerUpHalfHeight;
    float _boostPowerUpDensity;
    float _boostPowerUpActionTime;
    float _boostSpeedToIncrease;
    float _boostNewDrive;

    float _rockHalfWidth;
    float _rockHalfHeight;
    float _rockDensity;
    float _velToReduce;
    float _healthToReduce;
    int _rockTimeOfAction;
    int _rockDriveToReduce;

    float _mudHalfWidth;
    float _mudHalfHeight;
    float _mudDensity;
    float _mudTime;

    float _oilHalfWidth;
    float _oilHalfHeight;
    float _oilDensity;
    float _newDamping;
    float _oilTime;

public:
    Configuration();
    float getGravityX();
    float getGravityY();
    float getFPS();
    float getVelocityIterations();
    float getPositionIterations();
    float getMaxDistToTrack();
    int getModifiersCreationFrequency();
    std::string getMapToUse();
    int getMaxLaps();

    float getCarWidth();
    float getCarHeight();
    float getCarMaxHealth();

    float getMaxForwardSpeed();
    float getMaxForwardDrive();
    float getMaxBackwardsSpeed();
    float getMaxBackwardDrive();
    float getMaxForwardSpeedOnGrass();
    float getMaxForwardDriveOnGrass();
    float getMaxBackwardSpeedOnGrass();
    float getMaxBackwardDriveOnGrass();
    float getCurrentForwardSpeed();
    float getCurrentForwardDrive();
    float getCurrentBackwardSpeed();
    float getCurrentBackwardDrive();
    float getCarMaxLateralImpulse();
    float getCarAngularImpulse();
    float getCarDesiredTorque();
    float getLinearDamping();
    float getAngularDamping();
    float getLinearVelocityInit();
    float getAngularVelocityInit();
    float getCarDensity();
    float getCarFriction();

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
    int getHealthToIncrease();

    float getBoostPowerUpHalfWidth();
    float getBoostPowerUpHalfHeight();
    float getBoostPowerUpDensity();
    float getBoostPowerUpActionTime();
    float getBoostSpeedToIncrease();
    float getBoostNewDrive();

    float getRockHalfWidth();
    float getRockHalfHeight();
    float getRockDensity();
    float getRockVelToReduce();
    float getRockHealthToReduce();
    int getRockTimeOfAction();
    int getRockDriveToReduce();

    float getMudHalfWidth();
    float getMudHalfHeight();
    float getMudDensity();
    float getMudTime();

    float getOilHalfWidth();
    float getOilHalfHeight();
    float getOilDensity();
    float getOilTime();
    float getOilDamping();

};

#endif //MICROMACHINES_CONFIGURATION_H
