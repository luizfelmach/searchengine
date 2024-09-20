#ifndef VERTEX_H
#define VERTEX_H

#include "list.h"
#include "util.h"

typedef double        FLOAT; /* Only change precision here */
typedef struct vertex Vertex;

#define ALPHA 0.85

/**
 * Initializes a vertex.
 *
 * Uses malloc() from stdlib to allocate memory for the vertex.
 *
 * @param out Number of outgoing vertices.
 * @return Pointer to the vertex.
 */
Vertex* vertex_init(int out);

/**
 * Returns the number of outgoing vertices from a vertex.
 *
 * @param v Pointer to the vertex.
 * @return Number of outgoing vertices.
 */
int vertex_out(Vertex *v);

/**
 * Sets the number of outgoing vertices from a vertex.
 *
 * @param v Pointer to the vertex.
 * @param out Number of outgoing vertices.
 */
void    vertex_set_out(Vertex* v, int out);

/**
 * Returns the list of incoming vertices to a vertex.
 *
 * @param v Pointer to the vertex.
 * @return List of incoming vertices.
 */
List*   vertex_list_in(Vertex* v);

/**
 * Adds an incoming vertex to a vertex.
 *
 * @param v Pointer to the vertex.
 * @param w Pointer to the vertex to be added.
 * @return List of incoming vertices.
 */
List*   vertex_add_in(Vertex* v, Vertex* w);

/**
 * Returns the Page Rank of the vertex.
 *
 * @param v Pointer to the vertex.
 * @return Page Rank.
 */
FLOAT   vertex_pr(Vertex* v);

/**
 * Returns the last Page Rank of the vertex.
 *
 * @param v Pointer to the vertex.
 * @return Last Page Rank.
 */
FLOAT   vertex_pr_last(Vertex* v);

/**
 * Sets the Page Rank of the vertex.
 *
 * @param v Pointer to the vertex.
 * @param PR Page Rank.
 */
void    vertex_set_pr(Vertex* v, FLOAT PR);

/**
 * Sets the last Page Rank of the vertex.
 *
 * @param v Pointer to the vertex.
 * @param PR_LAST Last Page Rank.
 */
void    vertex_set_pr_last(Vertex* v, FLOAT PR_LAST);

/**
 * Calculates the Page Rank of a vertex.
 *
 * @param v Pointer to the vertex.
 * @param n_pages Number of pages.
 */
void    vertex_calculate_page_rank(Vertex* v, int n_pages);

/**
 * Destroys a vertex.
 *
 * Uses free() from stdlib to free the memory allocated for the vertex and deallocate the list of incoming vertices.
 *
 * @param v Pointer to the vertex.
 */
void vertex_destroy(Vertex *v);

#endif