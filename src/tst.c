#include "tst.h"

typedef char Chunk;

struct tst {
    TstValue value;
    Chunk    c;
    Tst *    l, *m, *r;
};

Tst* tst_node_create() {
    Tst* t = calloc(1, sizeof(Tst));
    return t;
}

Tst* tst_init() {
    return NULL;
}

Tst* tst_rec_insert(Tst* t, char* key, TstValue value, int d) {
    Chunk c = key[d];
    if (t == NULL) {
        t    = tst_node_create();
        t->c = c;
    }
    if (c < t->c) {
        t->l = tst_rec_insert(t->l, key, value, d);
    } else if (c > t->c) {
        t->r = tst_rec_insert(t->r, key, value, d);
    } else if (d < strlen(key) - 1) {
        t->m = tst_rec_insert(t->m, key, value, d + 1);
    } else {
        t->value = value;
    }
    return t;
}

Tst* tst_insert(Tst* t, char* key, TstValue value) {
    return tst_rec_insert(t, key, value, 0);
}

Tst* tst_rec_search(Tst* t, char* key, int d) {
    if (t == NULL) {
        return NULL;
    }
    Chunk c = key[d];
    if (c < t->c) {
        return tst_rec_search(t->l, key, d);
    } else if (c > t->c) {
        return tst_rec_search(t->r, key, d);
    } else if (d < strlen(key) - 1) {
        return tst_rec_search(t->m, key, d + 1);
    } else {
        return t;
    }
}

Tst* tst_iter_search(Tst* t, char* key) {
    int d = 0;
    while (t != NULL) {
        Chunk c = key[d];
        if (c < t->c) {
            t = t->l;
        } else if (c > t->c) {
            t = t->r;
        } else {
            if (d < strlen(key) - 1) {
                t = t->m;
                d++;
            } else {
                return t;
            }
        }
    }
    return NULL;
}

TstValue tst_search(Tst* t, char* key) {
    // t = tst_rec_search(t, key, 0);
    t = tst_iter_search(t, key);
    if (t == NULL) {
        return NULL;
    } else {
        return t->value;
    }
}

void tst_rec_keys(Tst* t, char* buffer, int d) {
    if (t == NULL) {
        return;
    }

    tst_rec_keys(t->l, buffer, d);

    buffer[d] = t->c;

    if (t->value) {
        buffer[d + 1] = '\0';
        printf("'%s' ", buffer);
    }

    tst_rec_keys(t->m, buffer, d + 1);

    tst_rec_keys(t->r, buffer, d);
}

void tst_keys(Tst* t) {
    char stack[1024];  // Maximum string size
    tst_rec_keys(t, stack, 0);
}

void tst_destroy(Tst* t) {
    if (t == NULL) return;
    tst_destroy(t->l);
    tst_destroy(t->m);
    tst_destroy(t->r);
    free(t);
}

void tst_destroy_fn(Tst* t, tst_free_fn free_fn) {
    if (t == NULL) return;
    tst_destroy_fn(t->l, free_fn);
    tst_destroy_fn(t->m, free_fn);
    tst_destroy_fn(t->r, free_fn);
    if (t->value) free_fn(t->value);
    free(t);
}