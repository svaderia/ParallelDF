#include <stdio.h>
#include <stdlib.h>
#include "myTrie.h"

#ifndef _MY_HEAP
#define _MY_HEAP

struct MaxHeapNode{
	// TrieNode* tnode;
    char* word;
	int frequency;
};
typedef struct MaxHeapNode MaxHeapNode;

MaxHeapNode** maxHeapify(MaxHeapNode** arr, int last, int t);

int maxIndex(MaxHeapNode** arr, int one, int two);

MaxHeapNode** buildHeap(MaxHeapNode** arr, int size);

MaxHeapNode** make_heap_from_trie(TrieNode* root, MaxHeapNode** arr, int* arr_size, int* capacity, int alpha, char* buffer, int iter);

void print_topk(MaxHeapNode** arr, int* size, int k);

void print(MaxHeapNode** arr, int size);

#endif