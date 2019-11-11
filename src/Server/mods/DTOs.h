#ifndef MICROMACHINES_DTOS_H
#define MICROMACHINES_DTOS_H

struct CarDTO {
    float x;
    float y;
    float angle;
    float maxForwardSpeed;
    float lapsCompleted;
    size_t health;
};



struct WorldDTO {
    CarDTO cars[10];

};


#endif //MICROMACHINES_DTOS_H
