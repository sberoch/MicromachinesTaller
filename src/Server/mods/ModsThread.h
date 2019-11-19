#ifndef MICROMACHINES_MODSTHREAD_H
#define MICROMACHINES_MODSTHREAD_H

#include <dlfcn.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Plugin.h"
#include "DTOs.h"

typedef void* dynamic_lib_handle;

static void close_lib(dynamic_lib_handle handle){
    dlclose(handle);
}

struct dynamic_lib {
    dynamic_lib_handle handle;
    std::string	path;

    dynamic_lib(std::string p) : path(p), handle(nullptr) {}

    ~dynamic_lib() {
        if (handle != nullptr)
            close_lib(handle);
    }
};

class ModsThread {
private:
    std::vector<dynamic_lib> libs;
    int unique_signal;
    std::vector<Plugin*> plugins;

    WorldDTO_t* _worldDTO;

    dynamic_lib_handle load_lib(const std::string& path);
    Plugin* instantiate(const dynamic_lib_handle handle);

public:
    ModsThread(const std::string& libs_filename, WorldDTO_t* worldDTO);
    void run();
    ~ModsThread() = default;
};

#endif //MICROMACHINES_MODSTHREAD_H
