#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/core.h"
#include "../include/rbtree.h"
#include "../include/tst.h"

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

    Tst *tst_stop_words = make_stop_words(f_stop_words);

    char *testes[] = {"Luiz",  "Vitor", "Felipe", "Ana",
                      "where", "Where", "where\n"};

    for (int i = 0; i < 7; i++) {
        printf("Tem %s : %s\n", testes[i],
               (tst_search(tst_stop_words, testes[i]) ? "YES" : "NO"));
    }

    tst_destroy(tst_stop_words);

    fclose(f_index);
    fclose(f_stop_words);
    fclose(f_graph);

    free(index);
    free(stop_words);
    free(graph);

    return EXIT_SUCCESS;
}
