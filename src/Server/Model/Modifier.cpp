#include "Modifier.h"

std::shared_ptr<Modifier> Modifier::makeModifier(std::shared_ptr<b2World> world, const size_t& type, const size_t& id, const float& x_init,
                                 const float& y_init, const float& angle, std::shared_ptr<Configuration> configuration){
    switch (type) {
        case TYPE_HEALTH_POWERUP :
            return std::shared_ptr<Modifier>(new HealthPowerup(world, type, id, x_init, y_init, angle, configuration));
        case TYPE_BOOST_POWERUP :
            return std::shared_ptr<Modifier>(new BoostPowerup(world, type, id, x_init, y_init, angle, configuration));
        case TYPE_ROCK :
            return std::shared_ptr<Modifier>(new Rock(world, type, id, x_init, y_init, angle, configuration));
        case TYPE_MUD :
            return std::shared_ptr<Modifier>(new Mud(world, type, id, x_init, y_init, angle, configuration));
        case TYPE_OIL :
            return std::shared_ptr<Modifier>(new Oil(world, type, id, x_init, y_init, angle, configuration));
    }

}
