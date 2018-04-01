#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "myRead.h"

int offset = 0;
bool eof = false;

FILE *getStream(FILE *fp, char* b, int k)
{	int count = -1;
	if (!eof)
        count = fread(b, 1, k, fp);
    //hack
    if(count < k) eof = true ;
    b[count] = '\0';
    return fp;
}

char* getWord(FILE* fp, char* b, int k){
    char* temp = (char*) malloc(MAX_WORD_SIZE * sizeof(char));
    int i = 0;
    memset(temp, 0, MAX_WORD_SIZE);
    while(1){
        if (offset == k || strlen(b) == 0 || b[offset] == '\0'){
			if( eof ){
				return temp;
			}
			memset(b, 0, k);
            fp = getStream(fp, b, k);
            offset = 0;
		}
        if(('a' <= b[offset] && b[offset] <= 'z') || ('A' <= b[offset] && b[offset] <= 'Z')){
            temp[i++] = b[offset++];
            if(temp[i-1] >= 'A' && temp[i-1] <= 'Z'){
                temp[i-1] += 'a' - 'A';
            }
        }else{
            offset++;
            if(temp[0] == '\0') continue;
            else return temp;
        }
    }
}

char** read_arr(FILE* fptr, int* size){

    *size = 32;
    char* temp = (char*) malloc(25 * sizeof(char));
    char** list_of_words = (char**) malloc((*size) * sizeof(char*));
    int i = 0, garbage, len;
    for(i = 0; ; i++){
        memset(temp, '\0', 25 * sizeof(char));
        garbage = fscanf(fptr, "%s", temp);
        len = strlen(temp);

        if(garbage == 0 || feof(fptr) || garbage == EOF){
            break;
        }

        list_of_words[i] = (char*) malloc((len + 1) * sizeof(char));
        memcpy(list_of_words[i], temp, (len + 1) * sizeof(char));
        // printf("%s\n", list_of_words[i]);

        if(i >= (*size) - 2){
            list_of_words = (char**) realloc(list_of_words, (*size) * 2 * sizeof(char**));
            (*size) = (*size) * 2;
        }
    }

    *size = i;
    return list_of_words;
}

bool search(char** arr, char* key, int lo, int hi){

    int what;
    while(lo <= hi){
        int mid = (lo + hi)/2;
        if((what = strcmp(arr[mid], key)) == 0){
            return true;
        }else if(what > 0){
            hi = mid - 1;
        }else{
            lo = mid + 1;
        }
    }
    return false;
}

// int main(){
//     char* b = (char*) malloc(4096 * sizeof(char));
//     int k = 4096;
//     memset(b, 0, k);
//     int i = 0;
//     char* temp;
//     FILE* fp = fopen("test", "r");

//     // while(1){
//     //     printf("%s\n", getWord(fp, b, k));
//     //     if( offset >= strlen(b) && eof ) break;        
//     // }
    
//     int file_count;
//     // char** filelist = list_dir(".", &file_count);

//     char** old_file_list = list_dir(".", &file_count);
//     char** file_list = append_paths(".", old_file_list, file_count);

//     // printf("%d", file_count);
//     for(i=0; i < file_count; i++){
//         printf("%s\n", file_list[i]);
//     }

// }