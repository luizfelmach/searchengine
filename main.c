#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rbtree.h"

int *i32(int a) {
    int *b = calloc(1, sizeof(int));
    *b     = a;
    return b;
}

int i32_cmp(void *a, void *b) {
    return *(int *)b - *(int *)a;
}

int main() {
    RBTree *tree = rbtree_init();

    printf("INICIO: %p\n", tree);

    for (int i = 0; i < 1000000; i++) {
        tree = rbtree_add(tree, i32_cmp, i32(i), NULL);
    }

    RBIterator *it = rbiterator_init(tree);

    for (RBTree *i = rbiterator_next(it); i != NULL; i = rbiterator_next(it)) {
        printf("%d %p\n", *(int *)rbtree_key(i), rbtree_value(i));
        free(rbtree_key(i));
    }

    rbtree_destroy(tree);
    rbiterator_destroy(it);

    return 0;
}