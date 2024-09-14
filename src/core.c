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
    return NULL;
}

int _rbtree_cmp_(RBKey a, RBKey b) {
    return strcmp((const char *)a, (const char *)b);
}

Tst *indexer(List *pages, Tst *stop_words) {
    Tst* page_words = tst_init();

    for (List *i = pages; i != NULL; i = list_next(i)) {
 
        char* filename = make_file_name("in/pages", "/", (char*)list_item(i));
        // printf("page: %s\n", filename);
        FILE *f_page = fopen(filename, "r");

        if (!f_page) {
            printf("error: could not open page file!\n");
            exit(EXIT_FAILURE);
        }

        size_t len = 0;
        char  *line = NULL;
        char* token = NULL;

        printf("before getline\n");
        while ((getline(&line, &len, f_page)) != -1) {
            printf("line: %s\n", line);
            token = strtok(line, " \n\t");
            printf("token: (%s)", token);

            while(token != NULL) {
                token[strlen(token) - 1] = '\0';
                to_lower(token);
                printf("token_upd: (%s)", token); // token updated
                
                if (tst_search(stop_words, token) != NULL) continue; // token is a stop word

                RBTree* rbt_pages = tst_search(page_words, token);
                
                if (rbt_pages == NULL) { // token does not exist at page_words TST
                    rbt_pages = rbtree_init();
                    rbt_pages = rbtree_add(rbt_pages, _rbtree_cmp_, (char*)list_item(i), NULL);
                    page_words = tst_insert(page_words, token, rbt_pages);
                }
                else {
                    if (rbtree_search(rbt_pages, _rbtree_cmp_, (char*)list_item(i)) == NULL) { // token does exist at page_words TST, but current page does not exist at the token's rbt_pages RBT
                        rbt_pages = rbtree_add(rbt_pages, _rbtree_cmp_, (char*)list_item(i), NULL);
                    }
                }

                token = strtok(NULL, " \n\t");
            }
        }   
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

void eval_page_rank(List *pages, Tst *vertices);

char *make_file_name(char *directory, char *path, char *file) {
    int   size   = strlen(directory) + strlen(path) + strlen(file) + 10;
    char *string = (char *)calloc(size, sizeof(char));
    sprintf(string, "%s/%s/%s", directory, path, file);
    return string;
}

List *filter_pages_by_term(List *pages, List *terms);
