#ifndef MICROMACHINES_DTOS_H
#define MICROMACHINES_DTOS_H

#include <stdio.h>

#define MAX_CARS 4
#define MAX_TRACKS 30

typedef struct CarDTO {
    float x;
    float y;
    float angle;
    float maxForwardSpeed;
    float lapsCompleted;
    size_t health;
    int id;
} CarDTO_t;

typedef struct TrackDTO {
    float x; //Center of mass in x axis
    float y; //Center of mass in y axis
    float halfWidth;
    float halfHeight;
    bool start;
} TrackDTO_t;

typedef struct WorldDTO {
    CarDTO_t cars[MAX_CARS];
    size_t cars_size;

    TrackDTO_t track[MAX_TRACKS];
    size_t track_size;
} WorldDTO_t;


#endif
