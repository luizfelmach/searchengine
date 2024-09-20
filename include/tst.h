#ifndef TST_H
#define TST_H

#include <stdio.h>
#include <stdlib.h>

#include "string.h"

typedef struct tst Tst;
typedef void*      TstValue;
typedef void (*tst_free_fn)(void*);

/**
 * Initializes a tst.
 *
 * Initializes the root of the tst as NULL.
 *
 * @return NULL.
 */
Tst*     tst_init();

/**
 * Inserts a key-value pair in the tst.
 *
 * Inserts a key-value pair in the tst. If the key already exists, the value is updated.
 *
 * @param t Pointer to the tst.
 * @param key Key to be inserted.
 * @param value Value to be inserted.
 * @return Pointer to the tst.
 */
Tst*     tst_insert(Tst* t, char* key, TstValue value);

/**
 * Searches for a key in the tst.
 *
 * Searches for a key in the tst. If the key is found, the value is returned.
 *
 * @param t Pointer to the tst.
 * @param key Key to be searched.
 * @return Value of the key.
 */
TstValue tst_search(Tst* t, char* key);

/**
 * Prints the keys of the tst.
 *
 * Prints the keys of the tst in ascending order.
 *
 * @param t Pointer to the tst.
 */
void     tst_keys(Tst* t);

/**
 * Destroys the tst.
 *
 * Destroys the tst and deallocates the memory used by it.
 *
 * @param t Pointer to the tst.
 */
void     tst_destroy(Tst* t);

/**
 * Destroys the tst with a custom free function.
 *
 * Destroys the tst and deallocates the memory used by it using a custom free function.
 *
 * @param t Pointer to the tst.
 * @param free_fn Custom free function.
 */
void     tst_destroy_fn(Tst* t, tst_free_fn free_fn);

#endif
