#ifndef RBTREE_H
#define RBTREE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct rbtree     RBTree;
typedef struct rbiterator RBIterator;
typedef void             *RBKey;
typedef void             *RBValue;
typedef int (*rbtree_cmp)(void *, void *);

RBTree *rbtree_init();
RBTree *rbtree_add(RBTree *rb, rbtree_cmp cmp, RBKey key, RBValue value);
RBTree *rbtree_search(RBTree *rb, rbtree_cmp cmp, RBKey key);
RBKey   rbtree_key(RBTree *rb);
RBValue rbtree_value(RBTree *rb);
void    rbtree_destroy(RBTree *rb);

RBIterator *rbiterator_init(RBTree *rb);
bool        rbiterator_hasnext(RBIterator *it);
RBTree     *rbiterator_next(RBIterator *it);
void        rbiterator_destroy(RBIterator *it);

#endif
