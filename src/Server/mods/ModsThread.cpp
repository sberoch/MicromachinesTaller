#include "ModsThread.h"

ModsThread::ModsThread(std::string libs_filename) : unique_signal(42) {
    try {
        std::cout << "Opening: " << libs_filename << std::endl;
        std::ifstream fs(libs_filename);
        std::string tmp;

        // read from the file.
        while(std::getline(fs, tmp))
            libs.push_back(dynamic_lib(tmp));
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void ModsThread::run() {
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
        //p->run(&world);
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
    return dlopen(path.data() , RTLD_NOW); // get a handle to the lib, may be nullptr.
// RTLD_NOW ensures that all the symbols are resolved immediately. This means that
// if a symbol cannot be found, the program will crash now instead of later.
}