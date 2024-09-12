#ifndef VERTEX_H
#define VERTEX_H

#include "list.h"

typedef double FLOAT; /* Only change precision here */

// TODO: Move this block to .c
struct {
    List* in;          /* Vertices in */
    int   out;         /* Size of vertices out  */
    FLOAT PR, PR_LAST; /* Page Rank */
} vertex;

typedef struct vertex Vertex;

Vertex* vertex_init(int out);
List*   vertex_list_in(Vertex* v);
List*   vertex_add_in(Vertex* v, Vertex* w);
FLOAT   vertex_pr(Vertex* v);
FLOAT   vertex_pr_last(Vertex* v);
void    vertex_set_pr(Vertex* v, FLOAT PR);
void    vertex_set_pr_last(Vertex* v, FLOAT PR_LAST);
void    vertex_calculate_page_rank(Vertex* v);

#endif