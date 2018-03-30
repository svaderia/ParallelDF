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

struct Stack{
	Node* head;
	Node* tail;
	unsigned int size;
};
typedef struct Stack Stack;

Stack* new_stack(void);
// Returns an initialized Stack structure.

Node* create_node(void* data);
// Returns a Node structure initialized by data Element.

Stack* push(Stack* stack, void* data);
// Adds a Node with data Element to the front of the Stack.

Stack* pop(Stack* stack);
// Deletes a Node from the front of the stack.

void* top(Stack* stack);
// Returns the element on top of the stack.

bool is_empty(Stack* stack);
// Return true if stack is empty, false otherwise.

#endif