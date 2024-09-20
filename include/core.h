#ifndef CORE_H
#define CORE_H

#define STOP_WORDS_FILE "stopwords.txt"
#define GRAPH_FILE "graph.txt"
#define INDEX_FILE "index.txt"
#define SEARCHES_FILE "searches.txt"
#define SOL_FILE "output.txt"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "rbtree.h"
#include "tst.h"
#include "util.h"
#include "vertex.h"

/**
 * Lower the characters of a string.
 *
 * @param str Pointer to the string.
 */
void to_lower(char *str);

/**
 * Get the pages from the index file.
 *
 * @param index_file Pointer to the index file.
 * @param n_pages Pointer to the number of pages.
 * 
 * @return Pointer to the list of pages.
 */
List *get_pages(FILE *index_file, int *n_pages);

/**
 * Construct the graph from the graph file.
 * 
 * Use a tst to map doc into vertex.
 *
 * @param graph_file Pointer to the graph file.
 * 
 * @return Pointer to the tst of vertices.
 */
Tst *make_vertices(FILE *graph_file);

/**
 * Construct the word indexer.
 * 
 * Map a word to a rbtree with the pages that contain the word.
 *
 * @param directory Pointer to the directory containing the pages.
 * @param pages Pointer to the list of pages.
 * @param stop_words Pointer to the stop words tst.
 * 
 * @return Pointer to the word indexer tst.
 */
Tst *indexer(char *directory, List *pages, Tst *stop_words);

/**
 * Construct the stop words tst.
 *
 * @param stop_words_file Pointer to the stop words file.
 * 
 * @return Pointer to the stop words tst.
 */
Tst *make_stop_words(FILE *stop_words_file);

/**
 * Evaluate the page rank of the vertices.
 *
 * @param pages Pointer to the list of pages.
 * @param vertices Pointer to the tst of vertices.
 * @param n_pages Number of pages.
 */
void eval_page_rank(List *pages, Tst *vertices, int n_pages);

/**
 * Construct the path of a file.
 * 
 * @param directory Pointer to the name of the directory.
 * @param path Pointer to the path inside the directory.
 * @param file Pointer to the name of the file.
 * 
 * @return Pointer to the path of the file.
 */
char *make_file_name(char *directory, char *path, char *file);

/**
 * Filter the pages by the terms.
 *
 * @param page_words Pointer to the word indexer.
 * @param terms Pointer to the list of terms.
 * @param n_terms Number of terms.
 * @param n_filtered_pages Pointer to the number of filtered pages.
 * 
 * @return Pointer to the list of filtered pages.
 */
List *filter_pages_by_term(Tst *page_words, List *terms, int n_terms,
                           int *n_filtered_pages);

#endif