#include "util.h"

char *read_lim(FILE *file, char lim) {
    char *buffer = NULL;
    size_t len = 0;
    int nread = getdelim(&buffer, &len, lim, file);
    if (nread <= 0) {
        free(buffer);
        return NULL;
    }
    buffer[nread-1] = '\0';
    return buffer;
}