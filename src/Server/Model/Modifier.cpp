#include "Modifier.h"

Modifier* Modifier::makeModifier(b2World* world, const size_t& type, const size_t& id, const float& x_init,
                                 const float& y_init, const float& angle, std::shared_ptr<Configuration> configuration){
    switch (type) {
        case TYPE_HEALTH_POWERUP :
            return new HealthPowerup(world, type, id, x_init, y_init, angle, configuration);
            break;
        case TYPE_BOOST_POWERUP :
            return new BoostPowerup(world, type, id, x_init, y_init, angle, configuration);
            break;
        case TYPE_ROCK :
            return new Rock(world, type, id, x_init, y_init, angle, configuration);
            break;
        case TYPE_MUD :
            return new Mud(world, type, id, x_init, y_init, angle, configuration);
            break;
        case TYPE_OIL :
            return new Oil(world, type, id, x_init, y_init, angle, configuration);
            break;
    }

}
