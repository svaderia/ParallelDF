#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "myStack.h"

const char* _MEM_ALLOC_ERROR_MSG = "Error in Heap Memory allocation.";
const char* _EMPTY_LIST_ERROR = "List is already empty. No more deletion possible.";

List* create_list(){
	List* temp = (List*) malloc(sizeof(List));
	if(temp == NULL){
		printf("%s :: Linked List\n", _MEM_ALLOC_ERROR_MSG);
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

List* push(List* list, void* data){
	Node* new_node = create_node(data);
	if(new_node == NULL){
		return NULL;
	}
	
	if(list -> size == 0){
		list -> head = new_node;
		list -> tail = new_node;
	}else{
		new_node -> next = list -> head;
		list -> head = new_node;
	}
	list -> size ++;

	return list;
}

List* pop(List* list){
	Node* del_node = list -> head;

	if(list -> size == 0){
		printf("%s\n", _EMPTY_LIST_ERROR);
		return NULL;
	}else if(list -> size == 1){
		list -> head = NULL;
		list -> tail = NULL;
		free(del_node);
	}else{
		list -> head = list -> head -> next;
		free(del_node);
	}
	list -> size --;

	return list;
}

bool is_empty(List* list){
	if(list -> size == 0){
		return true;
	}else{
		return false;
	}
}