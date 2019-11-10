/* Used by: https://unix.stackexchange.com/questions/226524/what-system-call-is-used-to-load-libraries-in-linux/462710#462710 */

#define _XOPEN_SOURCE 700
#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "plugin.h"

int main(void) {
    int (*plugin_func)(void);
    /*int (*b)(void);*/
    char *error;

    void* handle = dlopen("plugin.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror();
    plugin_func = (int (*)(void)) dlsym(handle, "plugin_func");
    /*b = (int (*)(void)) dlsym(handle, "b");*/
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    printf("Calling plugin\n");
    int ret = plugin_func();
    printf("Plugin returned %d\n", ret);
    /*assert(a() == 1);
    assert(b() == 2);*/
    if (dlclose(handle) != 0) {
        fprintf(stderr, "Could not close plugin: %s\n", dlerror());
        return 1;
    }
    return EXIT_SUCCESS;
}
