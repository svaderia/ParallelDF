#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** add_file(char** arr, int* size, int* capacity, char* path){
    if((*size) >= (*capacity)){
        arr = (char**) realloc(arr, 2  * (*capacity) * sizeof(char*));
        (*capacity) *= 2;
    }

    int len = strlen(path);
    arr[*size] = (char*) malloc((len + 1) * sizeof(char));
    memset(arr[*size], '\0', (len + 1) * sizeof(char));
    memcpy(arr[*size], path, len * sizeof(char));
    (*size) += 1;

    return arr;
}

char** listdir(const char *name, char** arr, int* size, int* capacity)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return arr;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            arr = listdir(path, arr, size, capacity);
        } else {
            char file_path[1024];
            snprintf(file_path, sizeof(file_path), "%s/%s", name, entry->d_name);
            // printf("%s\n",file_path);
            arr = add_file(arr, size, capacity, file_path);
        }
    }
    closedir(dir);
    return arr;
}

// int main(void) {

//     int size = 0, capacity = 2;
//     char** arr = (char**) malloc(capacity * sizeof(char*));
//     arr = listdir("/home/shyamal/Personal/GitHub", arr, &size, &capacity);

//     int i;
//     for(i = 0; i < size; i ++){
//         printf("%s\n", arr[i]);
//     }

//     return 0;
// }