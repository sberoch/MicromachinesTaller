#ifndef MICROMACHINES_DESTRUCTIONLISTENER_H
#define MICROMACHINES_DESTRUCTIONLISTENER_H

#include <Box2D/Box2D.h>
#include "FixtureUserData.h"

class DestructionListener : public b2DestructionListener{
public:
    void SayGoodbye(b2Fixture* fixture);

    void SayGoodbye(b2Joint* joint);
};

#endif //MICROMACHINES_DESTRUCTIONLISTENER_H
