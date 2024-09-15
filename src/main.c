#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"
#include "list.h"
#include "rbtree.h"
#include "tst.h"
#include "util.h"

void debug_pages(List *pages);
void debug_stop_words(Tst *stop_words);
void debug_tst_vertices(Tst *vertices);
void debug_tst_page_words(Tst *page_words);

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *index      = make_file_name(argv[1], "/", INDEX_FILE);
    char *stop_words = make_file_name(argv[1], "/", STOP_WORDS_FILE);
    char *graph      = make_file_name(argv[1], "/", GRAPH_FILE);

    FILE *f_index      = fopen(index, "r");
    FILE *f_stop_words = fopen(stop_words, "r");
    FILE *f_graph      = fopen(graph, "r");

    free(index);
    free(stop_words);
    free(graph);

    if (!f_index || !f_stop_words || !f_graph) {
        printf("error: could not open files\n");
        return EXIT_FAILURE;
    }

    int n_pages = 0;
    List *pages          = get_pages(f_index, &n_pages);
    Tst  *tst_stop_words = make_stop_words(f_stop_words);
    Tst  *tst_page_words = indexer(argv[1], pages, tst_stop_words);
    Tst  *tst_vertices   = make_vertices(f_graph);
    eval_page_rank(pages, tst_vertices, n_pages);

    debug_pages(pages);
    debug_stop_words(tst_stop_words);
    debug_tst_vertices(tst_vertices);
    debug_tst_page_words(tst_page_words);

    // RBTree     *rb = tst_search(tst_page_words, "g");
    // RBIterator *it = rbiterator_init(rb);
    //
    // for (RBTree *i = rb; i != NULL; i = rbiterator_next(it)) {
    //    printf("'%s' ", (char *)rbtree_key(i));
    //}
    //
    // rbiterator_destroy(it);

    fclose(f_index);
    fclose(f_stop_words);
    fclose(f_graph);

    FORL(i, pages) free(list_item(i));
    tst_destroy(tst_stop_words);
    tst_destroy_fn(tst_vertices, (void *)vertex_destroy);
    tst_destroy_fn(tst_page_words, (void *)rbtree_destroy);
    list_destroy(pages);

    return EXIT_SUCCESS;
}

void debug_pages(List *pages) {
    printf("PAGES: [ ");
    FORL(i, pages) {
        printf("'%s' ", (char *)list_item(i));
    }
    printf("]\n\n");
}

void debug_stop_words(Tst *stop_words) {
    printf("STOP WORDS: [ ");
    tst_keys(stop_words);
    printf("]\n\n");
}

void debug_tst_vertices(Tst *vertices) {
    printf("VERTICES: [ ");
    tst_keys(vertices);
    printf("]\n\n");
}

void debug_tst_page_words(Tst *page_words) {
    printf("PAGE WORDS: [ ");
    tst_keys(page_words);
    printf("]\n\n");
}
