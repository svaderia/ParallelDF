#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "myStack.h"

#ifndef _TRAVERSAL
#define _TRAVERSAL

void* get_next_file(Stack* stack);
// Returns a file for thread to process.

bool isdir(void* pT);
// Returns True if pT is a directory.

void* get_file_children(void* pT, int* num_files);
// Returns a list of file type children in pT if pT is a directory. Stores the number of files in num_files.

void* get_dir_children(void* pT, int* num_dirs);
// Returns a list of directory type children in pT if pT is a directory. Stores the number of files in num_dirs.

#endif