#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "_LINKED_LIST.h"

#ifndef _TRIE
#define _TRIE

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

#define ALPHABET_SIZE 26

struct TrieNode{
    struct TrieNode** children; //[ALPHABET_SIZE];
    bool end;
    unsigned int frequency;
    unsigned int last_doc;
};

typedef struct TrieNode TrieNode;

TrieNode* get_Node(void);

TrieNode* trie_insert(TrieNode *root, char *key);

TrieNode* trie_merge(TrieNode *croot1,TrieNode *croot2);

char* convert_to_lower(char* str);

char index_to_char(int index);

int doc_free(TrieNode* dnode);

#endif
