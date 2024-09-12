#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "rbtree.h"
#include "tst.h"
#include "vertex.h"

void to_lower(char *str);

Tst *make_stop_words(FILE *stop_words_file);

Tst *indexer(List *pages, Tst *stop_words);

Tst *make_vertices(FILE *graph_file);

void eval_page_rank(List *pages, Tst *vertices);

List *filter_pages_by_term(List *pages, List *terms);

#endif