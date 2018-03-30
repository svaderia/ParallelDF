#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef _MY_STACK
#define _MY_STACK

struct Node{
	void* ele;
	struct Node* next;
};
typedef struct Node Node;

struct List{
	Node* head;
	Node* tail;
	unsigned int size;
};
typedef struct List List;

List* create_list(void);
// Returns an initialized List structure.

Node* create_node(void* data);
// Returns a Node structure initialized by data Element.

List* push(List* list, void* data);
// Adds a Node with data Element to the front of the List.

List* pop(List* list);
// Deletes a Node from the front of the list.

bool is_empty(List* list);
// Return true if list is empty, false otherwise.

#endif