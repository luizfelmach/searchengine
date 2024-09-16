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

typedef struct {
    FLOAT PR;
    char *page;
} TOSORT;

int _double_cmp(const void *a, const void *b) {
    TOSORT *aa = (TOSORT *)a;
    TOSORT *bb = (TOSORT *)b;
    if (aa->PR > bb->PR) return -1;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *index      = make_file_name(argv[1], "/", INDEX_FILE);
    char *stop_words = make_file_name(argv[1], "/", STOP_WORDS_FILE);
    char *graph      = make_file_name(argv[1], "/", GRAPH_FILE);
    char *searches   = make_file_name(argv[1], "/", SEARCHES_FILE); // talvez n vamos precisar desse arquivo
    char *output        = make_file_name(argv[1], "/", SOL_FILE);

    FILE *f_index      = fopen(index, "r");
    FILE *f_stop_words = fopen(stop_words, "r");
    FILE *f_graph      = fopen(graph, "r");
    FILE *f_searches   = fopen(searches, "r");
    FILE *f_out        = fopen(output, "w");

    free(index);
    free(stop_words);
    free(graph);
    free(searches);
    free(output);

    if (!f_index || !f_stop_words || !f_graph || !f_searches || !f_out) {
        printf("error: could not open files\n");
        return EXIT_FAILURE;
    }

    int   n_pages        = 0;
    List *pages          = get_pages(f_index, &n_pages);
    Tst  *tst_stop_words = make_stop_words(f_stop_words);
    Tst  *tst_page_words = indexer(argv[1], pages, tst_stop_words);
    Tst  *tst_vertices   = make_vertices(f_graph);
    eval_page_rank(pages, tst_vertices, n_pages);

    debug_pages(pages);
    debug_stop_words(tst_stop_words);
    debug_tst_vertices(tst_vertices);
    debug_tst_page_words(tst_page_words);

    char *line;
    while ((line = read_lim(f_searches, '\n')) != NULL) {
        List *terms   = list_init();
        to_lower(line);

        int n_terms = 0;
        FORW(word, line, " ") {
            terms = list_push_back(terms, word);
            n_terms+=1;
        }

        int   n_filtered_pages = 0;
        List *filtered_pages =
            filter_pages_by_term(tst_page_words, terms, n_terms, &n_filtered_pages);

        TOSORT *page_sort = malloc(n_filtered_pages * sizeof(TOSORT));

        int i = 0;
        FORL(p, filtered_pages) {
            Vertex *v    = tst_search(tst_vertices, list_item(p));
            page_sort[i] = (TOSORT){.page = list_item(p), .PR = vertex_pr(v)};
            i += 1;
        }

        qsort(page_sort, n_filtered_pages, sizeof(TOSORT), _double_cmp);

        printf("search:");
        fprintf(f_out, "search:");
        FORL(p, terms) {
            printf("%s ", (char*)list_item(p));
            fprintf(f_out, "%s ", (char*)list_item(p));
        }
        printf("\n");
        fprintf(f_out, "\n");
        printf("pages:");
        fprintf(f_out, "pages:");
        for (int i = 0; i < n_filtered_pages; i++) {
            printf("%s ", page_sort[i].page);
            fprintf(f_out, "%s ", page_sort[i].page);
        }
        printf("\n");
        fprintf(f_out, "\n");
        printf("pr:");
        fprintf(f_out, "pr:");
        for (int i = 0; i < n_filtered_pages; i++) {
            printf("%.8lf ", page_sort[i].PR);
            fprintf(f_out, "%.8lf ", page_sort[i].PR);
        }
        printf("\n");
        fprintf(f_out, "\n");

        free(line);
        free(page_sort);
        list_destroy(terms);
        list_destroy(filtered_pages);
    }

    fclose(f_index);
    fclose(f_stop_words);
    fclose(f_graph);
    fclose(f_searches);
    fclose(f_out);

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
