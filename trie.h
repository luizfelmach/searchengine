#ifndef TRIE_H
#define TRIE_H

#include "string.h"

typedef struct trie Trie;

Trie* trie_insert(Trie* t, String key, int val);
int   trie_search(Trie* t, String key);

#endif