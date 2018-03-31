#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "myStack.h"

#ifndef _TRAVERSAL
#define _TRAVERSAL

struct FileNode{
	char* name;
	int depth;
};
typedef struct FileNode FileNode;


FileNode* get_next_file(Stack* stack, int last_depth);
// Returns a file for thread to process.

bool is_directory(char *path);
// Returns True if pT is a directory.

bool is_file(char *path);
// Returns True if pT is a file

char** get_file_list(char* folder_name, int* file_count);
// Returns a list of file type children in pT if pT is a directory. Stores the number of files in num_files.

char** get_dir_list(char* folder_name, int* dir_count);
// Returns a list of directory type children in pT if pT is a directory. Stores the number of files in num_dirs.

Stack* push_multiple(Stack* stack, FileNode** data, int size);
// Adds Nodes with data Element to the front of the Stack.

#endif