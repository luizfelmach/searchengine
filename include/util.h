#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

// Macro for iterate over a string with strtok()
#define FORW(i, str, del) \
    for (char *i = strtok(str, del); i != NULL; i = strtok(NULL, del))

// Macro for iterate over a list
#define FORL(i, list) for (List *i = list; i != NULL; i = list_next(i))

/**
 * Reads a line from a file.
 *
 * @param file Pointer to the file.
 * @param lim Limiting character.
 * 
 * @return Pointer to the line.
 */
char *read_lim(FILE *file, char lim);

#endif