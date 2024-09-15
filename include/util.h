#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

#define FORW(i, str, del) for (char * i=strtok(str, del); i != NULL; i = strtok(NULL, del))

/* Ler pelo delimitador, removendo o >>>DELIMITADOR<<<. Aprenda criador do C.
 * urrh */
char *read_lim(FILE *file, char lim);

#endif