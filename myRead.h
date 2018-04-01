#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#ifndef _TOKEN
#define _TOKEN
#define MAX_WORD_SIZE 140

extern int offset;

extern bool eof;

typedef char* buffer;

char** read_arr(FILE* fptr, int* size);

bool search(char** arr, char* key, int lo, int hi);

char* getWord(FILE* fp, char* b, int k);

#endif