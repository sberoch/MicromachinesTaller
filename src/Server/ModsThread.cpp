#include <zconf.h>
#include <sys/param.h>
#include "ModsThread.h"

ModsThread::ModsThread(const std::string& libs_filename, WorldDTO_t* worldDTO) : unique_signal(42), _worldDTO(worldDTO) {
    try {
        std::cout << "Opening: " << libs_filename << std::endl;
        std::ifstream fs(libs_filename);
        std::string tmp;

        // read from the file.
        while(std::getline(fs, tmp))
            libs.emplace_back(tmp);

        // load up all the libs
        for (auto& l : libs) {
            l.handle = load_lib(l.path);
        }


    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void ModsThread::run() {
    //TODO: see why p is hpu
    plugins.clear();
    // instantiate!
    for (auto& l : libs)
        plugins.push_back( instantiate(l.handle) );

    // call each plugin's run func.
    for (Plugin* p : plugins) {
        if (p == nullptr) continue;
        std::cout << p->message() << std::endl;
        p->run(_worldDTO);
        delete p;
    }
}

Plugin* ModsThread::instantiate(const dynamic_lib_handle handle) {
    if (handle == nullptr) return nullptr;

    void *maker = dlsym(handle , "factory");

    if (maker == nullptr) return nullptr;

    typedef Plugin* (*fptr)();
    fptr func = reinterpret_cast<fptr>(reinterpret_cast<void*>(maker));

    return func();
}

dynamic_lib_handle ModsThread::load_lib(const std::string &path) {
    std::cout << "Trying to open: " << path << std::endl;
    void* shared_lib = dlopen(path.data(), RTLD_NOW);
    const char* err = dlerror();
    if (!shared_lib) {
        printf("dlopen failed: %s\n", err);
        return nullptr;
    }
    return shared_lib;
}


