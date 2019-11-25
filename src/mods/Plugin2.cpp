#include <string>
#include <iostream>
#include "Plugin.h"

//Plugin to create random modifiers.
class Plugin2 : public Plugin {
private:
    int _modifierTypes[MODIFIER_TYPES];

    int getInactiveModifier(WorldDTO* world){
        for (size_t i=0; i<MAX_MODIFIERS; ++i){
            if (!world->modifiers[i].active)
                return i;
        }
        return -1;
    }

public:
    Plugin2(){
        _modifierTypes[0] = TYPE_HEALTH_POWERUP;
        _modifierTypes[1] = TYPE_BOOST_POWERUP;
        _modifierTypes[2] = TYPE_OIL;
        _modifierTypes[3] = TYPE_MUD;
        _modifierTypes[4] = TYPE_ROCK;
    }

    void run(WorldDTO* world){
        int inactiveModifier = getInactiveModifier(world);
        if (inactiveModifier != -1){
            srand(time(NULL));
            int rand = std::rand() % world->track_size;

            TrackDTO randomTrack = world->track[rand];

            float xhi = randomTrack.x - randomTrack.halfWidth;
            float xlo = randomTrack.x + randomTrack.halfWidth;

            float yhi = randomTrack.y - randomTrack.halfHeight;
            float ylo = randomTrack.y + randomTrack.halfHeight;


            world->modifiers[inactiveModifier].x = xlo + static_cast <float> (std::rand()) /( static_cast <float> (RAND_MAX/(xhi-xlo)));
            world->modifiers[inactiveModifier].y = ylo + static_cast <float> (std::rand()) /( static_cast <float> (RAND_MAX/(yhi-ylo)));
            world->modifiers[inactiveModifier].angle = randomTrack.angle;

            int modifierType = std::rand() % MODIFIER_TYPES;
            world->modifiers[inactiveModifier].type = _modifierTypes[modifierType];

            world->modifiers[inactiveModifier].newModifier = true;
            world->modifiers[inactiveModifier].active = true;

            world->modifiers[inactiveModifier].id = world->max_id;
            world->max_id++;
        }
    }

    ~Plugin2() = default;
};

extern "C" Plugin* factory(void) {
    return static_cast<Plugin*>(new Plugin2);
}
