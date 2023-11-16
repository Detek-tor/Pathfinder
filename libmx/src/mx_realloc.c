#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    size_t old_size;
    void *tmp;

    if (ptr == 0)
	    return malloc(size);
    
    old_size = malloc_size(ptr);

    if (size <= old_size)
	    return ptr;

    tmp = malloc(size);
    mx_memcpy(tmp, ptr, old_size);
    free(ptr);
    return tmp;
}
