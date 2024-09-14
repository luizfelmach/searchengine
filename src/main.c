#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"
#include "list.h"
#include "rbtree.h"
#include "tst.h"
#include "util.h"

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // O "/" indica que ta na raiz da pasta informada
    // Vai ser util para iterar sobre os documento na pagina
    // por exemplo: make_file_name(argv[1], "/pages", DOCUMENTO[i])
    char *index      = make_file_name(argv[1], "/", INDEX_FILE);
    char *stop_words = make_file_name(argv[1], "/", STOP_WORDS_FILE);
    char *graph      = make_file_name(argv[1], "/", GRAPH_FILE);

    FILE *f_index      = fopen(index, "r");
    FILE *f_stop_words = fopen(stop_words, "r");
    FILE *f_graph      = fopen(graph, "r");

    if (!f_index || !f_stop_words || !f_graph) {
        printf("error: could not open files\n");
        free(index);
        free(stop_words);
        free(graph);
        return EXIT_FAILURE;
    }

    List *pages          = get_pages(f_index);
    Tst  *tst_stop_words = make_stop_words(f_stop_words);
    Tst  *tst_vertices   = make_vertices(f_graph);

    char *testes[] = {"Luiz",  "Vitor",   "Felipe",   "Ana",  "where",
                      "Where", "where\n", "of",       "of\n", "no",
                      "no\n",  "against", "against\n"};

    for (int i = 0; i < 13; i++) {
        printf("Tem %s : %s\n", testes[i],
               (tst_search(tst_stop_words, testes[i]) ? "YES" : "NO"));
    }

    for (List *i = pages; i != NULL; i = list_next(i)) free(list_item(i));
    tst_destroy(tst_stop_words);
    list_destroy(pages);

    fclose(f_index);
    fclose(f_stop_words);
    fclose(f_graph);

    free(index);
    free(stop_words);
    free(graph);

    return EXIT_SUCCESS;
}
