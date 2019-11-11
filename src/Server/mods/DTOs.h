#ifndef MICROMACHINES_DTOS_H
#define MICROMACHINES_DTOS_H

typedef struct CarDTO {
    float x;
    float y;
    float angle;
    float maxForwardSpeed;
    float lapsCompleted;
    size_t health;
} CarDTO_t;



struct WorldDTO {
    CarDTO_t cars[10];

};


#endif
