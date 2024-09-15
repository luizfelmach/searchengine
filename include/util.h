#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

#define FORW(i, str, del) \
    for (char *i = strtok(str, del); i != NULL; i = strtok(NULL, del))

#define FORL(i, list) for (List *i = list; i != NULL; i = list_next(i))

/* Ler pelo delimitador, removendo o >>>DELIMITADOR<<<. Aprenda criador do C.
 * urrh */
char *read_lim(FILE *file, char lim);

#endif