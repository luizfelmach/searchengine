#include "../include/core.h"

void to_lower(char *str);

Tst *make_vertices(FILE *graph_file);

Tst *indexer(List *pages, Tst *stop_words);

Tst *make_stop_words(FILE *stop_words_file)
{
    Tst* stop_words = tst_init();
    char* line = NULL;
    size_t len = 0; 
    int i = 0;

    while (getline(&line, &len, stop_words_file) != -1) 
    {
        i++;
        stop_words = tst_insert(stop_words, line, malloc(sizeof(int)));
        printf ("%d - stop word added!\n", i);
    }

    free(line);
    
    return stop_words;
}

void eval_page_rank(List *pages, Tst *vertices);

char* make_file_name (char* directory, char* file)
{   

    int size = strlen(directory) + strlen(file) + 1;
    char* string = (char*)calloc(size, sizeof(char));

    strcpy(string, directory);
    strcat(string, file);
    
    printf ("%s\n", string);

    return string;
}

List *filter_pages_by_term(List *pages, List *terms);