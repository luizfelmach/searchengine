#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>

#include "string.h"

typedef struct trie Trie;
typedef void*       TrieValue;

Trie*     trie_init();
Trie*     trie_insert(Trie* t, char* key, TrieValue value);
TrieValue trie_search(Trie* t, char* key);
void      trie_destroy(Trie* t);

#endif
