#include "core.h"

void to_lower(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] = str[i] - 'A' + 'a';
    }
}

List *get_pages(FILE *index_file, int* n_pages) {
    List *pages = list_init();
    *n_pages = 0;
    char *line;

    while ((line = read_lim(index_file, '\n')) != NULL) {
        pages = list_push_front(pages, line);
        *n_pages += 1;
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

int _rbtree_cmp_(RBKey a, RBKey b) {
    return strcmp((const char *)a, (const char *)b);
}

Tst *indexer(List *pages, Tst *stop_words) {
    Tst *page_words = tst_init();

    FORL(page, pages) {
        // printf("%s: ", list_item(page));
        char *filename = make_file_name("in", "/pages", list_item(page));
        FILE *f_page   = fopen(filename, "r");

        char *line;
        while ((line = read_lim(f_page, '\n')) != NULL) {
            to_lower(line);

            FORW(word, line, " \t") {
                if (tst_search(stop_words, word) != NULL) continue;

                RBTree *rbt_pages = tst_search(page_words, word);

                if (!rbt_pages) {
                    rbt_pages = rbtree_init();
                }

                rbt_pages =
                    rbtree_add(rbt_pages, _rbtree_cmp_, list_item(page), NULL);

                page_words = tst_insert(page_words, word, rbt_pages);

                // printf("(%s) ", word);
            }

            free(line);
        }

        // printf("\n\n");

        fclose(f_page);
        free(filename);
    }

    return page_words;
}


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

void eval_page_rank(List *pages, Tst *vertices, int n_pages) {
    int n = n_pages;

    FORL(page, pages) {
        Vertex* v = tst_search(vertices, list_item(page));
        vertex_set_pr_last(v, (FLOAT)1/n);
        vertex_set_pr(v, 1000.0);
    }

    FLOAT EPS = 10e-6;

    while(1) {
        FLOAT ERROR = 0.0;

        FORL(page, pages) {
            Vertex* v = tst_search(vertices, list_item(page));
            vertex_calculate_page_rank(v, n);
            ERROR += abs(vertex_pr(v) - vertex_pr_last(v));
        }

        ERROR /= n;

        if (ERROR < EPS) break;

        FORL(page, pages) {
            Vertex* v = tst_search(vertices, list_item(page));
            vertex_set_pr_last(v, vertex_pr(v));
        }
    }
}

char *make_file_name(char *directory, char *path, char *file) {
    int   size   = strlen(directory) + strlen(path) + strlen(file) + 10;
    char *string = (char *)calloc(size, sizeof(char));
    sprintf(string, "%s/%s/%s", directory, path, file);
    return string;
}

List *filter_pages_by_term(List *pages, List *terms);
