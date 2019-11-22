#include "DestructionListener.h"

void DestructionListener::SayGoodbye(b2Fixture *fixture) {
    if ( FixtureUserData* fud = (FixtureUserData*) fixture->GetUserData() )
        delete fud;
}

void DestructionListener::SayGoodbye(b2Joint *joint) {}