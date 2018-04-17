#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "myStack.h"
#include "traversal.h"

Stack* push_multiple(Stack* stack, FileNode** data, int size){
	int i;
	for(i = size - 1; i >= 0; i--){
		stack = push(stack, data[i]);
	}
	return stack;
}

FileNode** pTs_to_push(char** items, int depth, int num_items){
	FileNode** ret = (FileNode**) malloc(num_items * sizeof(FileNode*));
	int iter, len;
	for(iter = 0; iter < num_items; iter++){
		ret[iter] = (FileNode*) malloc(sizeof(FileNode));
		len = strlen(items[iter]);
		ret[iter] -> name = (char*) malloc((len + 1) * sizeof(char));
		memset(ret[iter] -> name, '\0', (len + 1) * sizeof(char));
		memcpy(ret[iter] -> name, items[iter], (len) * sizeof(char));
	
		// strcpy(ret[iter] -> name, items[iter]);
		ret[iter] -> depth = depth;
	}
	return ret;
}

FileNode* get_next_file(Stack* stack, int last_depth){
	FileNode* pT = (FileNode*) top(stack);
	char cwd[1024];
	memset(cwd, '\0', 1024 * sizeof(char));
    if(pT == NULL) return NULL;
    
	int curr_depth = pT -> depth;
	int num_files;
	int num_dirs;
	while(!is_empty(stack)){
		pT = (FileNode*) top(stack);
		stack = pop(stack);

        if(curr_depth - (pT -> depth) > 0){
            while(curr_depth - (pT -> depth) > 0){
                chdir("..");
                getcwd(cwd, sizeof(cwd));
                // printf("cwd cd: %s\n", cwd);
                curr_depth --;
		    }

            // while(depth_diff){
            //     chdir("..");
            //     getcwd(cwd, sizeof(cwd));
            //     printf("cwd dd: %s\n", cwd);
            //     depth_diff --;
            // }
        }else{
            while(last_depth - (pT -> depth) > 0){
                chdir("..");
                getcwd(cwd, sizeof(cwd));
                // printf("cwd ld: %s\n", cwd);
                last_depth --;
            }
        }

		if(is_directory(pT -> name)){

			char** files = get_file_list(pT -> name, &num_files);
			char** dirs = get_dir_list(pT -> name, &num_dirs);

            chdir(pT -> name);
			getcwd(cwd, sizeof(cwd));
			// printf("cwd: %s\n", cwd);

			FileNode** files_to_push = pTs_to_push(files, (pT -> depth) + 1, num_files);
			FileNode** dirs_to_push = pTs_to_push(dirs, (pT -> depth) + 1, num_dirs);
			
			if(num_dirs != 0){
				stack = push_multiple(stack, dirs_to_push, num_dirs);
			}

			if(num_files != 0){
				stack = push_multiple(stack, files_to_push, num_files);	
			}

			curr_depth ++;
			continue;
		}else{
			break;
		}
	}
	return pT;
}

void dfs(Stack* stack){
    if(is_empty(stack)) return ;
    FileNode* pT = (FileNode*) top(stack);
    stack = pop(stack);
    int num_files, num_dirs;
    if(is_directory(pT->name)){
        char** files = get_file_list(pT -> name, &num_files);
        char** dirs = get_dir_list(pT -> name, &num_dirs);
        chdir(pT->name);
        
        FileNode** files_to_push = pTs_to_push(files, (pT -> depth) + 1, num_files);
        FileNode** dirs_to_push = pTs_to_push(dirs, (pT -> depth) + 1, num_dirs);
        
        if(num_dirs != 0){
            stack = push_multiple(stack, dirs_to_push, num_dirs);
        }
        if(num_files != 0){
            stack = push_multiple(stack, files_to_push, num_files);	
        }
            dfs(stack);
            chdir("..");
    }else{
        char cwd[1024];
        memset(cwd, '\0', 1024 * sizeof(char));
        getcwd(cwd, sizeof(cwd));
        char* new_file_list = (char*) malloc( (strlen(cwd) + strlen(pT->name) + 2) * sizeof(char) );
        strcpy(new_file_list, cwd);
        strcat(new_file_list, "/");
        strcat(new_file_list, pT->name);
        printf("%s\n", new_file_list);
        dfs(stack);
    }

}

void print_stack(Stack* stack){
    Node* temp = stack -> head;
    while(temp != NULL){
        printf("%s;\t", ((FileNode*)(temp -> ele)) -> name);
        temp = temp -> next;
    }
    printf("\n");
}

// int main(){

// 	Stack* stack = new_stack();
// 	FileNode* temp = (FileNode*) malloc(sizeof(FileNode));
//     char* path = "/home/shyamal/Test";
//     int len = strlen(path) + 1;
// 	temp -> name = (char*) malloc(len * sizeof(char));
// 	memset(temp -> name, '\0', len * sizeof(char));
// 	memcpy(temp -> name, path ,  (len - 1)* sizeof(char));
// 	temp -> depth = 1;
// 	stack = push(stack, temp);

//     dfs(stack);
//     // int last_depth = 1;
// 	// FileNode* pT = get_next_file(stack, last_depth);
//     // // print_stack(stack);
// 	// printf("%s\n", pT -> name);
// 	// while(true){
//     //     last_depth = pT -> depth;
//     //     pT = get_next_file(stack, last_depth);
//     //     // print_stack(stack);
//     // 	if(pT == NULL) break;
//     //     if(is_directory(pT->name)) break;
//     //     printf("%s\n", pT -> name);
//     // }

// 	return 0;
// }