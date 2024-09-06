#include "string.h"

int string_cl(String s) {
    int size = 0;

    while (*s != 0) {
        size += 1;
        s += 1;
    }

    return size;
}

String string_an(String s) {
    int s_size   = strlen((char *)s);
    int new_size = s_size + (s_size - s_size % sizeof(Chunk)) + sizeof(Chunk);
    String new   = calloc(new_size, sizeof(char));
    strcpy((char *)new, (char *)s);
    free(s);
    return new;
}
