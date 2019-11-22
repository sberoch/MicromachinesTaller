#ifndef MICROMACHINES_DTOS_H
#define MICROMACHINES_DTOS_H

#include <stdio.h>
#include "../Common/Constants.h"

#define MAX_CARS 4
#define MAX_TRACKS 200
#define MAX_MODIFIERS 10
#define MODIFIER_TYPES 5

typedef struct CarDTO {
    float x;
    float y;
    float angle;
    float _maxForwardSpeed;
    float maxForwardDrive;
    float lapsCompleted;
    size_t health;
    int id;
} CarDTO_t;

typedef struct TrackDTO {
    float x; //Center of mass in x axis
    float y; //Center of mass in y axis
    float halfWidth;
    float halfHeight;
    float angle;
    bool start;
} TrackDTO_t;

typedef struct ModifierDTO {
    size_t id;
    size_t type;
    float x;
    float y;
    float angle;
    bool newModifier;
    bool active;
} ModifierDTO_t;

typedef struct WorldDTO {
    CarDTO_t cars[MAX_CARS];
    size_t cars_size;

    TrackDTO_t track[MAX_TRACKS];
    size_t track_size;

    ModifierDTO_t modifiers[MAX_MODIFIERS];
    size_t max_id;
} WorldDTO_t;


#endif
