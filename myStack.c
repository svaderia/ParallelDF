#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "myStack.h"

const char* _MEM_ALLOC_ERROR_MSG = "Error in Heap Memory allocation.";
const char* _EMPTY_LIST_ERROR = "Stack is already empty. No more deletion possible.";

Stack* new_stack(){
	Stack* temp = (Stack*) malloc(sizeof(Stack));
	if(temp == NULL){
		printf("%s :: Linked Stack\n", _MEM_ALLOC_ERROR_MSG);
		return NULL;
	}else{
		temp -> head = NULL;
		temp -> tail = NULL;
		temp -> size = 0;
		return temp;
	}
}

Node* create_node(void* data){
	Node* temp = (Node*) malloc(sizeof(Node));
	if(temp == NULL){
		printf("%s\n", _MEM_ALLOC_ERROR_MSG);
		return NULL;
	}else{
		temp -> ele = data;
		temp -> next = NULL;
		return temp;
	}
}

Stack* push(Stack* stack, void* data){
	Node* new_node = create_node(data);
	if(new_node == NULL){
		return NULL;
	}
	
	if(stack -> size == 0){
		stack -> head = new_node;
		stack -> tail = new_node;
	}else{
		new_node -> next = stack -> head;
		stack -> head = new_node;
	}
	stack -> size ++;

	return stack;
}

Stack* pop(Stack* stack){
	Node* del_node = stack -> head;

	if(stack -> size == 0){
		printf("%s\n", _EMPTY_LIST_ERROR);
		return NULL;
	}else if(stack -> size == 1){
		stack -> head = NULL;
		stack -> tail = NULL;
		free(del_node);
	}else{
		stack -> head = stack -> head -> next;
		free(del_node);
	}
	stack -> size --;

	return stack;
}

void* top(Stack* stack){
	return stack -> head -> ele;
}

bool is_empty(Stack* stack){
	if(stack -> size == 0){
		return true;
	}else{
		return false;
	}
}