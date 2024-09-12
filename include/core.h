#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "rbtree.h"
#include "tst.h"
// #include "vertex.h"

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
Tst *indexer(List *pages, Tst *stop_words);

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
void eval_page_rank(List *pages, Tst *vertices);

/**
 * @brief
 * 
 * @param 
 * 
 * @return 
 * 
 * @note 
 */
char* make_file_name (char* directory, char* file);

/**
 * @brief
 * 
 * @param 
 * 
 * @return 
 * 
 * @note 
 */
List *filter_pages_by_term(List *pages, List *terms);

#endif