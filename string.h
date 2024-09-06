#ifndef STRING_H
#define STRING_H

#include <math.h>
#include <stdlib.h>
#include <string.h>

// typedef char Chunk;
// typedef __int128 Chunk;
typedef short Chunk;
// typedef unsigned int Chunk;
// typedef unsigned long Chunk;
typedef Chunk* String;

/*
 * Return chunk len
 */
int string_cl(String s);

/*
 * Append NULL chunk in the end
 */
String string_an(String s);

#endif