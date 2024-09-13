#include "core.h"

void to_lower(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] = str[i] - 'A' + 'a';
    }
}

List *get_pages(FILE *index_file) {
    return NULL;
}

Tst *make_vertices(FILE *graph_file) {
    return NULL;
}

Tst *indexer(List *pages, Tst *stop_words);

Tst *make_stop_words(FILE *stop_words_file) {
    Tst   *stop_words = tst_init();
    char  *line       = NULL;
    size_t len        = 0;
    size_t read       = 0;

    while ((read = getline(&line, &len, stop_words_file)) != -1) {
        line[read - 1] = '\0';  // Substitui '\n' por '\0'
        to_lower(line);
        stop_words = tst_insert(stop_words, line, (void *)0x1);
    }

    free(line);
    return stop_words;
}

void eval_page_rank(List *pages, Tst *vertices);

char *make_file_name(char *directory, char *path, char *file) {
    int   size   = strlen(directory) + strlen(path) + strlen(file) + 10;
    char *string = (char *)calloc(size, sizeof(char));
    sprintf(string, "%s/%s/%s", directory, path, file);
    return string;
}

List *filter_pages_by_term(List *pages, List *terms);
