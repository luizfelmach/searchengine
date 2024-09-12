#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/rbtree.h"
#include "../include/tst.h"

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

    for (int i = 0; i < 100; i++) {
        tree = rbtree_add(tree, i32_cmp, i32(i), NULL);
    }

    RBIterator *it = rbiterator_init(tree);

    for (RBTree *i = rbiterator_next(it); i != NULL; i = rbiterator_next(it)) {
        printf("%d %p\n", *(int *)rbtree_key(i), rbtree_value(i));
        free(rbtree_key(i));
    }

    rbtree_destroy(tree);
    rbiterator_destroy(it);

    Tst *tst = tst_init();

    tst = tst_insert(tst, "pao", malloc(sizeof(int)));
    tst = tst_insert(tst, "top", malloc(sizeof(int)));
    tst = tst_insert(tst, "pedro", malloc(sizeof(int)));
    tst = tst_insert(tst, "joao", malloc(sizeof(int)));
    tst = tst_insert(tst, "pablo", malloc(sizeof(int)));

    printf("has %p\n", tst_search(tst, "pao"));
    printf("has %p\n", tst_search(tst, "top"));
    printf("has %p\n", tst_search(tst, ""));
    printf("has %p\n", tst_search(tst, "bla bla bla"));

    tst_destroy_fn(tst, free);

    return 0;
}