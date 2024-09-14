#include "core.h"

void to_lower(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] = str[i] - 'A' + 'a';
    }
}

List *get_pages(FILE *index_file) {
    List  *pages = list_init();
    char  *line  = NULL;
    size_t len   = 0;
    size_t read  = 0;

    while ((read = getline(&line, &len, index_file)) != -1) {
        if (line[read - 1] == '\n') line[read - 1] = '\0';
        pages = list_push_front(pages, strdup(line));
    }

    free(line);
    return pages;
}

void removeBarraN(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '\n') str[i] = '\0';
    }
}

Tst *make_vertices(FILE *graph_file) {
    Tst   *vertices = tst_init();
    char  *line     = NULL;
    size_t len      = 0;

    while (getline(&line, &len, graph_file) != -1) {
        char *token = strtok(line, " ");
        char *key   = strdup(token);
        free(key);

        token   = strtok(NULL, " ");
        int out = atoi(token);

        // Handle the first file in the line (parent)
        Vertex *parent = (Vertex *)tst_search(vertices, key);
        if (parent != NULL) {
            vertex_set_out(parent, out);
        } else {
            parent   = vertex_init(out);
            vertices = tst_insert(vertices, key, parent);
        }

        //printf("%d\n", vertex_out(parent));

        // Handle the rest of the files in the line (childrens)
        for (int i = 0; i < out; i++) {
            
            token = strtok(NULL, " ");

            if (i == out-1)
            {
                token[strlen(token) - 1] = '\0';
            }

            //if (token[strlen(token) - 1] == '\n')
            //    token[strlen(token) - 1] = 'B';
            printf("Key: '%s'\n", token);

            Vertex *children = (Vertex *)tst_search(vertices, token);
            if (children != NULL) {
                vertex_add_in(children, parent);
            } else {
                children = vertex_init(0);
                vertices = tst_insert(vertices, token, (void *)children);
                vertex_add_in(children, parent);
            }
        }
    }
    free(line);

    return vertices;
}

Tst *indexer(List *pages, Tst *stop_words);

Tst *make_stop_words(FILE *stop_words_file) {
    Tst   *stop_words = tst_init();
    char  *line       = NULL;
    size_t len        = 0;
    size_t read       = 0;

    while ((read = getline(&line, &len, stop_words_file)) != -1) {
        if (line[read - 1] == '\n') line[read - 1] = '\0';
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
