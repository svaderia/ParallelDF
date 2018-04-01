#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

TrieNode* trie_insert(TrieNode *root, char *key, int current_doc);

TrieNode* merge_trie(TrieNode *base,TrieNode *droot);

int* divide(int num_of_proc)

//char* convert_to_lower(char* str);

//char index_to_char(int index);

int trie_free(TrieNode* dnode);

#endif
