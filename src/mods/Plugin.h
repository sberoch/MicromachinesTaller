#ifndef _PLUGIN_H
#define _PLUGIN_H

#include "DTOs.h"
#include <string>

class Plugin {

public:
    virtual std::string message(void) = 0;

    virtual void run(WorldDTO* world) = 0;
};

#endif

