#include "rbtree.h"

#define RED true
#define BLACK false

struct rbtree {
    RBKey   key;
    RBValue value;
    bool    color;
    RBTree *l, *r;
};

RBTree *rbtree_node(RBKey key, RBValue value, bool color) {
    RBTree *node = calloc(1, sizeof(RBTree));
    node->key    = key;
    node->value  = value;
    node->color  = color;
    return node;
}

bool rbtnode_red(RBTree *x) {
    if (x == NULL) return BLACK;
    return x->color;  // RED == true
}

RBTree *rbtnode_rotate_left(RBTree *h) {
    RBTree *x   = h->r;
    h->r        = x->l;
    x->l        = h;
    x->color    = x->l->color;
    x->l->color = RED;
    return x;
}

RBTree *rbtnode_rotate_right(RBTree *h) {
    RBTree *x   = h->l;
    h->l        = x->r;
    x->r        = h;
    x->color    = x->r->color;
    x->r->color = RED;
    return x;
}

void rbtnode_flip_colors(RBTree *h) {
    h->color    = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}

RBTree *rbtree_init() {
    return NULL;
}

RBTree *rbtree_add(RBTree *rb, rbtree_cmp compare, RBKey key, RBValue value) {
    // Insert at bottom and color it red.
    if (rb == NULL) {
        return rbtree_node(key, value, RED);
    }

    int cmp = compare(key, rb->key);

    if (cmp < 0) {
        rb->l = rbtree_add(rb->l, compare, key, value);
    } else if (cmp > 0) {
        rb->r = rbtree_add(rb->r, compare, key, value);
    } else /*cmp == 0*/ {
        rb->value = value;
    }
    // Lean left.
    if (rbtnode_red(rb->r) && !rbtnode_red(rb->l)) {
        rb = rbtnode_rotate_left(rb);
    }
    // Balance 4-node.
    if (rbtnode_red(rb->l) && rbtnode_red(rb->l->l)) {
        rb = rbtnode_rotate_right(rb);
    }
    // Split 4-node.
    if (rbtnode_red(rb->l) && rbtnode_red(rb->r)) {
        rbtnode_flip_colors(rb);
    }

    return rb;
}

RBTree *rbtree_search(RBTree *rb, rbtree_cmp compare, RBKey key) {
    while (rb != NULL) {
        int cmp;
        cmp = compare(key, rb->key);
        if (cmp < 0)
            rb = rb->l;
        else if (cmp > 0)
            rb = rb->r;
        else
            return rb;
    }
    return NULL;
}

RBKey rbtree_key(RBTree *rb) {
    return rb->key;
}

RBValue rbtree_value(RBTree *rb) {
    return rb->value;
}

void rbtree_destroy(RBTree *rb) {
    if (rb == NULL) return;
    rbtree_destroy(rb->r);
    rbtree_destroy(rb->l);
    free(rb);
}

struct rbiterator {
    RBTree *stack[256];  // it takes 2²⁵⁶ keys in redblack to pop this stack!
    int top;
};

RBIterator *rbiterator_init(RBTree *rb) {
    RBIterator *it = calloc(1, sizeof(RBIterator));
    it->top        = 0;

    for (RBTree *i = rb; i != NULL; i = i->l) {
        it->stack[it->top++] = i;
    }

    return it;
}

bool rbiterator_hasnext(RBIterator *it) {
    return it->top > 0;
}

RBTree *rbiterator_next(RBIterator *it) {
    if (!rbiterator_hasnext(it)) return NULL;

    RBTree *t = it->stack[--it->top];

    for (RBTree *i = t->r; i != NULL; i = i->l) {
        it->stack[it->top++] = i;
    }

    return t;
}

void rbiterator_destroy(RBIterator *it) {
    free(it);
}