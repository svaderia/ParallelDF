#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "traversal.h"

bool is_file(char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return (bool)S_ISREG(path_stat.st_mode);
}

bool is_directory(char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return (bool)S_ISDIR(path_stat.st_mode);
}


char** get_file_list(char* folder_name, int* file_count){
    DIR *dir;
    struct dirent *ent;
    *file_count = 0;
    if ((dir = opendir (folder_name)) != NULL) {
        /* Count total files within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) { /* If the entry is a regular file */
                (*file_count)++;
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return NULL;
    }

    char** file_list = (char**) malloc((*file_count) * sizeof(char*));
    int i = 0;
    
    if ((dir = opendir (folder_name)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (ent->d_type == DT_REG){
                file_list[i] =  (char*) malloc((strlen(ent->d_name) + 1)*sizeof(char));
                strcpy(file_list[i], ent->d_name);
                // printf ("%s\n", file_list[i]);
                i++;
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return NULL;
    }
    return file_list;
}

char** get_dir_list(char* folder_name, int* dir_count){
    DIR *dir;
    struct dirent *ent;
    *dir_count = 0;
    if ((dir = opendir (folder_name)) != NULL) {
        /* Count total files within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_DIR) { /* If the entry is a regular Directory */
                (*dir_count)++;
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return NULL;
    }

    (*dir_count) -= 2;
    char** dir_List = (char**) malloc((*dir_count)  * sizeof(char*));
    int i = 0;
    
    if ((dir = opendir (folder_name)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (ent->d_type == DT_DIR){
                if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
                    dir_List[i] =  (char*) malloc((strlen(ent->d_name) + 1)*sizeof(char));
                    strcpy (dir_List[i], ent->d_name);
                    // printf ("%s\n", dir_List[i]);
                    i++;
                }
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return NULL;
    }
    return dir_List;
}

// int main(){
    
//     return 0;
// }