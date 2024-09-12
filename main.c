#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rbtree.h"
#include "trie.h"

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

    Trie *trie = trie_init();

    trie = trie_insert(trie, "pao", malloc(sizeof(int)));
    trie = trie_insert(trie, "top", malloc(sizeof(int)));
    trie = trie_insert(trie, "pedro", malloc(sizeof(int)));
    trie = trie_insert(trie, "joao", malloc(sizeof(int)));
    trie = trie_insert(trie, "pablo", malloc(sizeof(int)));

    printf("has %p\n", trie_search(trie, "pao"));
    printf("has %p\n", trie_search(trie, "top"));
    printf("has %p\n", trie_search(trie, ""));
    printf("has %p\n", trie_search(trie, "bla bla bla"));

    trie_destroy_fn(trie, free);

    return 0;
}