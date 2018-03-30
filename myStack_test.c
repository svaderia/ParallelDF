#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "myStack.h"

struct Element{
	int data;
};
typedef struct Element Element;

int main(){

	int i;

	Element* e1 = (Element*) malloc(sizeof(Element));
	Element* e2 = (Element*) malloc(sizeof(Element));
	Element* e3 = (Element*) malloc(sizeof(Element));
	e1 -> data = 1;
	e2 -> data = 2;
	e3 -> data = 3;

	List* temp = create_list();
	printf("%d\n", temp -> size);
	temp = push(temp, e1);
	temp = push(temp, e2);
	temp = push(temp, e3);
	printf("%d\n", temp -> size);
	printf("%d\n", ((Element*)(temp -> head -> ele)) -> data);
	printf("%d\n", ((Element*)(temp -> head -> next -> ele)) -> data);
	printf("%d\n", ((Element*)(temp -> head -> next -> next -> ele)) -> data);

	temp = pop(temp);

	printf("%d\n", temp -> size);
	printf("%d\n", ((Element*)(temp -> head -> ele)) -> data);

	temp = pop(temp);
	temp = pop(temp);

	bool test_empty = is_empty(temp);
	if(test_empty){
		printf("List is empty\n");
	}

	return 0;
}