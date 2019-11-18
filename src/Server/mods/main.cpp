#include <dlfcn.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Plugin.h"

typedef void* dynamic_lib_handle;

static dynamic_lib_handle load_lib(const std::string& path);

//static Plugin* instantiate(const dynamic_lib_handle handle);
static Plugin* instantiate(const dynamic_lib_handle handle) {

    if (handle == nullptr) return nullptr;

    void *maker = dlsym(handle , "factory");

    if (maker == nullptr) return nullptr;

    typedef Plugin* (*fptr)();
    fptr func = reinterpret_cast<fptr>(reinterpret_cast<void*>(maker));

    return func();
}

static void close_lib(dynamic_lib_handle handle);

struct dynamic_lib {
    dynamic_lib_handle handle;
    std::string	path;

    dynamic_lib(std::string p) : path(p), handle(nullptr) {}

    ~dynamic_lib() {
        if (handle != nullptr)
            close_lib(handle);
    }
};

int unique_signal = 42;

int main(int argc, char **argv) {
    if (argc < 2)
        return 1;

    std::vector<dynamic_lib> libs;

    try {
        std::cout << "Opening: " << argv[1] << std::endl;
        std::ifstream fs(argv[1]);
        std::string tmp;

        // read from the file.
        while(std::getline(fs, tmp))
            libs.push_back(dynamic_lib(tmp));
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 2;
    }

    // load up all the libs
    for (auto& l : libs) {
        l.handle = load_lib(l.path);
    }

    std::vector<Plugin*> plugins;
    // instantiate!
    for (auto& l : libs)
        plugins.push_back( instantiate(l.handle) );

    // call each widget's message() func.
    for (Plugin* p : plugins) {
        if (p == nullptr) continue;
        std::cout << p->message() << std::endl;
        delete p;
    }
}

static dynamic_lib_handle load_lib(const std::string& path) {
    std::cout << "Trying to open: " << path << std::endl;
    return dlopen(path.data() , RTLD_NOW); // get a handle to the lib, may be nullptr.
// RTLD_NOW ensures that all the symbols are resolved immediately. This means that
// if a symbol cannot be found, the program will crash now instead of later.
}

static void close_lib(dynamic_lib_handle handle) {
    dlclose(handle);
}