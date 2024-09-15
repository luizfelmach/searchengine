#include "vertex.h"

struct vertex {
    List* in;          /* Vertices in */
    int   out;         /* Size of vertices out  */
    FLOAT PR, PR_LAST; /* Page Rank */
};

Vertex* vertex_init(int out) {
    Vertex* v  = (Vertex*)malloc(sizeof(struct vertex));
    v->in      = list_init();
    v->out     = out;
    v->PR      = 0.0;
    v->PR_LAST = 0.0;
    return v;
}

int vertex_out(Vertex *v) {
    return v->out;
}

void vertex_set_out(Vertex* v, int out) {
    v->out = out;
}

List* vertex_list_in(Vertex* v) {
    return v->in;
}

List* vertex_add_in(Vertex* v, Vertex* w) {
    v->in = list_push_front(v->in, w);
    return v->in;
}

FLOAT vertex_pr(Vertex* v) {
    return v->PR;
}

FLOAT vertex_pr_last(Vertex* v) {
    return v->PR_LAST;
}

void vertex_set_pr(Vertex* v, FLOAT PR) {
    v->PR = PR;
}

void vertex_set_pr_last(Vertex* v, FLOAT PR_LAST) {
    v->PR_LAST = PR_LAST;
}

void vertex_calculate_page_rank(Vertex* v) {
    // TODO
}

void vertex_destroy(Vertex *v) {
    list_destroy(v->in);
    free(v);
}
