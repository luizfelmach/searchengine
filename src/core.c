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

char* extract_after_last_whitespace(char *line) {
    char *last_whitespace;

    // Find the last occurrence of space or tab
    last_whitespace = strrchr(line, '\t');
    if (last_whitespace == NULL) {
        last_whitespace = strrchr(line, ' ');  // If no tab, search for space
    }

    if (last_whitespace != NULL) {
        // Move past the last whitespace sequence
        while (*last_whitespace == ' ' || *last_whitespace == '\t') {
            last_whitespace++;
        }
    }

    return last_whitespace;
}

Tst *indexer(List *pages, Tst *stop_words) {
    Tst *page_words = tst_init();

    for (List *i = pages; i != NULL; i = list_next(i)) {

        printf("page: (%s)\n\n", (char*)list_item(i));
        char *filename = make_file_name("in/pages", "/", list_item(i));
        FILE *f_page = fopen(filename, "r");

        char *line, *token;

        while ((line = read_lim(f_page, '\n')) != NULL) {
            to_lower(line);

            // Process the last word/number separately (if applicable)
            // char *last_token = extract_after_last_whitespace(line);

            token = strtok(line, " \t");
            printf("token: (%s)\n", token);

            while (token != NULL) {
                
                if (tst_search(stop_words, token) != NULL) { // If the token is a stop word, skip it
                    token = strtok(NULL, " \t");
                    printf("token: (%s)\n", token);
                    continue;
                }

                // Insert token into the page_words tree
                RBTree *rbt_pages = tst_search(page_words, token);
                if (!rbt_pages) {
                    rbt_pages = rbtree_init();
                }
                rbt_pages = rbtree_add(rbt_pages, _rbtree_cmp_, list_item(i), NULL);
                page_words = tst_insert(page_words, token, rbt_pages);

                // Get the next token in the line
                token = strtok(NULL, " \t");
            }

            // Now handle the last token
            // if (last_token != NULL && tst_search(stop_words, last_token) == NULL) {
            //     printf("token: (%s)!\n", last_token);
            //     RBTree *rbt_pages = tst_search(page_words, last_token);
            //     if (!rbt_pages) {
            //         rbt_pages = rbtree_init();
            //     }
            //     rbt_pages = rbtree_add(rbt_pages, _rbtree_cmp_, list_item(i), NULL);
            //     page_words = tst_insert(page_words, last_token, rbt_pages);
            // }

            // Free the line after processing
            free(line);
        }

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

void eval_page_rank(List *pages, Tst *vertices);

char *make_file_name(char *directory, char *path, char *file) {
    int   size   = strlen(directory) + strlen(path) + strlen(file) + 10;
    char *string = (char *)calloc(size, sizeof(char));
    sprintf(string, "%s/%s/%s", directory, path, file);
    return string;
}

List *filter_pages_by_term(List *pages, List *terms);
