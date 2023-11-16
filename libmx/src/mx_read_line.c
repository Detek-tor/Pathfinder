#include "libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if (buf_size < 0 || fd < 0)
        return -2;

    (*lineptr) = (char *) mx_realloc(*lineptr, buf_size);
    mx_memset((*lineptr), '\0', malloc_size((*lineptr)));
    size_t bt = 0;
    char buffer;

    if (read(fd, &buffer, 1))
    {
        if (buffer == delim)
            return bt;

        (*lineptr) = (char *) mx_realloc(*lineptr, bt + 1);
        (*lineptr)[bt] = buffer;
        bt++;
    }
    else
        return -1;

    while (read(fd, &buffer, 1))
    {
        if (buffer == delim)
            break;

        if (bt >= buf_size)
            (*lineptr) = (char *) mx_realloc(*lineptr, bt + 1);

        (*lineptr)[bt] = buffer;

        bt++;
    }

    (*lineptr) = (char *) mx_realloc(*lineptr, bt + 1);

    size_t free_bt = malloc_size((*lineptr)) - bt;
    mx_memset(&(*lineptr)[bt], '\0', free_bt);

    return bt + 1;
}
