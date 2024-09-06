#include "trie.h"

struct trie {
    int   val;
    Chunk c;
    Trie *l, *m, *r;
};

Trie* trie_node_create() {
    Trie* t = calloc(1, sizeof(Trie));
    return t;
}

Trie* rec_insert(Trie* t, String key, int val, int d) {
    Chunk c = key[d];
    if (t == NULL) {
        t    = trie_node_create();
        t->c = c;
    }
    if (c < t->c) {
        t->l = rec_insert(t->l, key, val, d);
    } else if (c > t->c) {
        t->r = rec_insert(t->r, key, val, d);
    } else if (d < string_cl(key) - 1) {
        t->m = rec_insert(t->m, key, val, d + 1);
    } else {
        t->val = val;
    }
    return t;
}

Trie* trie_insert(Trie* t, String key, int val) {
    return rec_insert(t, key, val, 0);
}

Trie* rec_search(Trie* t, String key, int d) {
    if (t == NULL) {
        return NULL;
    }
    Chunk c = key[d];
    if (c < t->c) {
        return rec_search(t->l, key, d);
    } else if (c > t->c) {
        return rec_search(t->r, key, d);
    } else if (d < string_cl(key) - 1) {
        return rec_search(t->m, key, d + 1);
    } else {
        return t;
    }
}

int trie_search(Trie* t, String key) {
    t = rec_search(t, key, 0);
    if (t == NULL) {
        return -1;
    } else {
        return t->val;
    }
}