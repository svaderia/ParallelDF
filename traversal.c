#include <stdio.h>
#include <stdlib.h>
#include "myStack.h"

void* get_next_file(Stack* stack){
	while(!is_empty(stack)){
		void* pT = top(stack);
		stack = pop(stack);
		if(is_dir(pT)){
			int* num_files;
			int* num_dirs;
			void* files = get_file_children(pT, num_files);
			void* dirs = get_dir_children(pT, num_dirs);
			stack = push_multiple(stack, files, num_files);
			stack = push_multiple(stack, dirs, num_dirs);
			continue;
		}else{
			return pT;
		}
	}
}