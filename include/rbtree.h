#ifndef RBTREE_H
#define RBTREE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct rbtree     RBTree;
typedef struct rbiterator RBIterator;
typedef void             *RBKey;
typedef void             *RBValue;
typedef int (*rbtree_cmp)(void *, void *);

/**
 * Initializes a rbtree.
 *
 * Initializes the root of the rbtree as NULL.
 *
 * @return NULL.
 */
RBTree *rbtree_init();

/**
 * Adds a key-value pair in the rbtree.
 *
 * Adds a key-value pair in the rbtree. If the key already exists, the value is updated.
 *
 * @param rb Pointer to the rbtree.
 * @param cmp Comparison function.
 * @param key Key to be inserted.
 * @param value Value to be inserted.
 * @return Pointer to the rbtree.
 */
RBTree *rbtree_add(RBTree *rb, rbtree_cmp cmp, RBKey key, RBValue value);

/**
 * Searches for a key in the rbtree.
 *
 * Searches for a key in the rbtree. If the key is found, the value is returned.
 *
 * @param rb Pointer to the rbtree.
 * @param cmp Comparison function.
 * @param key Key to be searched.
 * @return Value of the key.
 */
RBTree *rbtree_search(RBTree *rb, rbtree_cmp cmp, RBKey key);

/**
 * Return a key of a node.
 *
 * @param rb Pointer to the rbtree node.
 * @return Pointer to key.
 */
RBKey   rbtree_key(RBTree *rb);

/**
 * Return a value of a node.
 *
 * @param rb Pointer to the rbtree node.
 * @return Pointer to value.
 */
RBValue rbtree_value(RBTree *rb);

/**
 * Destroys the rbtree.
 *
 * Destroys the rbtree and deallocates the memory used by it.
 *
 * @param t Pointer to the rbtree.
 */
void    rbtree_destroy(RBTree *rb);

/**
 * Initializes a rbtree iterator.
 *
 * Initializes the iterator of the rbtree.
 *
 * @param rb Pointer to the rbtree.
 * @return Pointer to the iterator.
 */
RBIterator *rbiterator_init(RBTree *rb);

/**
 * Checks if the iterator has a next element.
 *
 * Checks if the iterator has a next element.
 *
 * @param it Pointer to the iterator.
 * @return True if the iterator has a next element, false otherwise.
 */
bool        rbiterator_hasnext(RBIterator *it);

/**
 * Returns the next element of the iterator.
 *
 * Returns the next element of the iterator.
 *
 * @param it Pointer to the iterator.
 * @return Pointer to the next element.
 */
RBTree     *rbiterator_next(RBIterator *it);

/**
 * Destroys the rbtree iterator.
 *
 * Destroys the rbtree iterator and deallocates the memory used by it.
 *
 * @param it Pointer to the iterator.
 */
void        rbiterator_destroy(RBIterator *it);

#endif
