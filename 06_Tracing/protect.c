#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef int (*remove_type)(const char *file);
remove_type remove_base = NULL;

int remove(const char *file) {
    if (remove_base == NULL) {
        remove_base = (remove_type) (dlsym(RTLD_NEXT, "remove"));
    }

    if (strstr(file, "PROTECT") != NULL) {
        return 0;
    }
    return remove_base(file);
}
