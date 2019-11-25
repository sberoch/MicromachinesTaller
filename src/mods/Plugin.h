#ifndef _PLUGIN_H
#define _PLUGIN_H

#include "DTOs.h"
#include <string>

class Plugin {
public:
    virtual void run(WorldDTO* world) = 0;
    virtual ~Plugin() = default;
};

#endif

