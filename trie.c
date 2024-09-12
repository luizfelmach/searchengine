#include "trie.h"

typedef char Chunk;

struct trie {
    TrieValue value;
    Chunk     c;
    Trie *    l, *m, *r;
};

Trie* trie_node_create() {
    Trie* t = calloc(1, sizeof(Trie));
    return t;
}

Trie* trie_init() {
    return NULL;
}

Trie* rec_insert(Trie* t, char* key, TrieValue value, int d) {
    Chunk c = key[d];
    if (t == NULL) {
        t    = trie_node_create();
        t->c = c;
    }
    if (c < t->c) {
        t->l = rec_insert(t->l, key, value, d);
    } else if (c > t->c) {
        t->r = rec_insert(t->r, key, value, d);
    } else if (d < strlen(key) - 1) {
        t->m = rec_insert(t->m, key, value, d + 1);
    } else {
        t->value = value;
    }
    return t;
}

Trie* trie_insert(Trie* t, char* key, TrieValue value) {
    return rec_insert(t, key, value, 0);
}

Trie* rec_search(Trie* t, char* key, int d) {
    if (t == NULL) {
        return NULL;
    }
    Chunk c = key[d];
    if (c < t->c) {
        return rec_search(t->l, key, d);
    } else if (c > t->c) {
        return rec_search(t->r, key, d);
    } else if (d < strlen(key) - 1) {
        return rec_search(t->m, key, d + 1);
    } else {
        return t;
    }
}

TrieValue trie_search(Trie* t, char* key) {
    t = rec_search(t, key, 0);
    if (t == NULL) {
        return NULL;
    } else {
        return t->value;
    }
}

void trie_destroy(Trie* t) {
    if (t == NULL) return;
    trie_destroy(t->l);
    trie_destroy(t->m);
    trie_destroy(t->r);
    free(t);
}

void trie_destroy_fn(Trie* t, trie_free_fn free_fn) {
    if (t == NULL) return;
    trie_destroy_fn(t->l, free_fn);
    trie_destroy_fn(t->m, free_fn);
    trie_destroy_fn(t->r, free_fn);
    if (t->value) free_fn(t->value);
    free(t);
}