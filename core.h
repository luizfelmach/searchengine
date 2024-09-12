#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "rbtree.h"
#include "trie.h"
#include "vertex.h"

void to_lower(char *str);

Trie *make_stop_words(FILE *stop_words_file);

RBTree *indexer(List *pages, Trie *stop_words);

Trie *make_vertices(FILE *graph_file);

void eval_page_rank(List *pages, Trie *vertices);

List *filter_pages_by_term(List *pages, List *terms);

#endif