#ifndef CORE_H
#define CORE_H

#define STOP_WORDS_FILE "stopwords.txt"
#define GRAPH_FILE "graph.txt"
#define INDEX_FILE "index.txt"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "rbtree.h"
#include "tst.h"
#include "util.h"
#include "vertex.h"

/**
 * @brief
 *
 * @param
 *
 * @return
 *
 * @note
 */
void to_lower(char *str);

/**
 * @brief
 *
 * @param
 *
 * @return
 *
 * @note
 */
List *get_pages(FILE *index_file, int *n_pages);

/**
 * @brief
 *
 * @param
 *
 * @return
 *
 * @note
 */
Tst *make_vertices(FILE *graph_file);

/**
 * @brief
 *
 * @param
 *
 * @return
 *
 * @note
 */
Tst *indexer(char *directory, List *pages, Tst *stop_words);

/**
 * @brief
 *
 * @param
 *
 * @return
 *
 * @note
 */
Tst *make_stop_words(FILE *stop_words_file);

/**
 * @brief
 *
 * @param
 *
 * @return
 *
 * @note
 */
void eval_page_rank(List *pages, Tst *vertices, int n_pages);

/**
 * @brief
 *
 * @param
 *
 * @return
 *
 * @note
 */
char *make_file_name(char *directory, char *path, char *file);

/**
 * @brief
 *
 * @param
 *
 * @return
 *
 * @note
 */
List *filter_pages_by_term(Tst *page_words, List *terms, int n_terms,
                           int *n_filtered_pages);

#endif