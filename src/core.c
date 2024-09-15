#include "core.h"

void to_lower(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] = str[i] - 'A' + 'a';
    }
}

List *get_pages(FILE *index_file) {
    List *pages = list_init();
    char *line;

    while ((line = read_lim(index_file, '\n')) != NULL) {
        pages = list_push_front(pages, line);
    }

    return pages;
}

Tst *make_vertices(FILE *graph_file) {
    Tst  *vertices = tst_init();
    char *line;

    while ((line = read_lim(graph_file, '\n')) != NULL) {
        char *token = strtok(line, " ");
        char *key   = strdup(token);
        token       = strtok(NULL, " ");
        int out     = atoi(token);

        // Handle the first file in the line (parent)
        Vertex *parent = (Vertex *)tst_search(vertices, key);
        if (parent != NULL) {
            vertex_set_out(parent, out);
        } else {
            parent   = vertex_init(out);
            vertices = tst_insert(vertices, key, parent);
        }

        // Handle child
        FORW(file, NULL, " ") {
            Vertex *children = (Vertex *)tst_search(vertices, file);
            if (children != NULL) {
                vertex_add_in(children, parent);
            } else {
                children = vertex_init(0);
                vertices = tst_insert(vertices, file, children);
                vertex_add_in(children, parent);
            }
        }

        free(key);
        free(line);
    }

    return vertices;
}

Tst *indexer(List *pages, Tst *stop_words);

Tst *make_stop_words(FILE *stop_words_file) {
    Tst  *stop_words = tst_init();
    char *line;

    while ((line = read_lim(stop_words_file, '\n')) != NULL) {
        to_lower(line);
        stop_words = tst_insert(stop_words, line, (void *)0x1);
        free(line);
    }

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
