#ifndef TST_H
#define TST_H

#include <stdlib.h>

#include "string.h"

typedef struct tst Tst;
typedef void*      TstValue;
typedef void (*tst_free_fn)(void*);

Tst*     tst_init();
Tst*     tst_insert(Tst* t, char* key, TstValue value);
TstValue tst_search(Tst* t, char* key);
void     tst_destroy(Tst* t);
void     tst_destroy_fn(Tst* t, tst_free_fn free_fn);

#endif
