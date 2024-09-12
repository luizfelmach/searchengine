#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/rbtree.h"
#include "../include/core.h"
#include "../include/tst.h"

#define STOP_WORDS "stopwords.txt"
#define GRAPH "graph.txt"
#define INDEX "index.txt"

int *i32(int a) 
{
    int *b = calloc(1, sizeof(int));
    *b     = a;
    return b;
}

int i32_cmp(void *a, void *b) 
{
    return *(int *)b - *(int *)a;
}

int main (int argc, char *argv[]) 
{
    // RBTree *tree = rbtree_init();

    // printf("INICIO: %p\n", tree);

    // for (int i = 0; i < 100; i++) {
    //     tree = rbtree_add(tree, i32_cmp, i32(i), NULL);
    // }

    // RBIterator *it = rbiterator_init(tree);

    // for (RBTree *i = rbiterator_next(it); i != NULL; i = rbiterator_next(it)) {
    //     printf("%d %p\n", *(int *)rbtree_key(i), rbtree_value(i));
    //     free(rbtree_key(i));
    // }

    // rbtree_destroy(tree);
    // rbiterator_destroy(it);

    // Tst *tst = tst_init();

    // tst = tst_insert(tst, "pao", malloc(sizeof(int)));
    // tst = tst_insert(tst, "top", malloc(sizeof(int)));
    // tst = tst_insert(tst, "pedro", malloc(sizeof(int)));
    // tst = tst_insert(tst, "joao", malloc(sizeof(int)));
    // tst = tst_insert(tst, "pablo", malloc(sizeof(int)));

    // printf("has %p\n", tst_search(tst, "pao"));
    // printf("has %p\n", tst_search(tst, "top"));
    // printf("has %p\n", tst_search(tst, ""));
    // printf("has %p\n", tst_search(tst, "bla bla bla"));

    // tst_destroy_fn(tst, free);
    
    // -------------------------------------------------------------------------------

    char* stop_words = make_file_name (argv[1], STOP_WORDS);

    FILE* f_stop_words = fopen (stop_words, "r");
    
    if (f_stop_words == NULL)
    {   
        // printf ("SHIT\n");
        free (stop_words);
        return 1;
    } 

    // // char* index = make_file_name (argv[1], INDEX);
    // // free (index);

    // // char* graph = make_file_name (argv[1], GRAPH);
    // // free (graph);


    // // FILE* f_stop_words = fopen ("in/stopwords.txt", "r"); // change to dynamic

    // // if (f_stop_words == NULL)
    // // {
    // //     printf ("SHIT\n");
    // //     return 1;
    // // } 

    Tst* tst_stop_words = make_stop_words(f_stop_words);
    tst_destroy_fn(tst_stop_words, free);

    fclose (f_stop_words);
    free (stop_words);

    return 0;
}
