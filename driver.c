#include "myTrie.h"
#include "myStack.h"
#include "traversal.h"
#include "myRead.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <omp.h>

Stack* init_stack(char* path){
    Stack* stack = new_stack();
    FileNode* stack_init = (FileNode*) malloc(sizeof(FileNode));
    stack_init -> name = (char*) malloc((strlen(path) + 1) * sizeof(char));
    memset(stack_init -> name, '\0', (strlen(path) + 1) * sizeof(char));
    memcpy(stack_init -> name, path, strlen(path) * sizeof(char));
    stack_init -> depth = 1;
    stack = push(stack, stack_init);
    return stack;
}

TrieNode** init_tries(int size){
    TrieNode** trie_list = (TrieNode**) malloc(sizeof(TrieNode*) * size );
    int i;
    for( i = 0; i < size; i++){
        trie_list[i] = get_Node();
    }
    return trie_list;
}

char** load_stopwords(){
    FILE* fptr = fopen("stopwords", "r");
    int size;
    char** list_of_words = read_arr(fptr, &size);
    fclose(fptr);

    return list_of_words;
}

void process_doc(FILE* doc, TrieNode* doc_root, int current_doc, char** stopwords){
    char* b = (char*) malloc(4096 * sizeof(char));
    char* word_buffer;
    int k = 4096;

    offset = 0;
    eof = false;
    memset(b, 0, k);

    while(1){
        word_buffer = getWord(doc, b, k);
        if(search(stopwords, word_buffer, 0, 570) == 1){
            free(word_buffer);
            continue;
        }
        printf("%s\n", word_buffer);
        doc_root = trie_insert(doc_root, word_buffer, current_doc);
        free(word_buffer);
        if( offset >= strlen(b) && eof ) break;
    }
}

TrieNode* merge_all(TrieNode* g_trie, TrieNode** trie_list, int num_threads, int alpha){
    int i;
    for(i = 0; i < num_threads; i++){
        g_trie = merge_trie(g_trie -> children [alpha], trie_list[i] -> children [alpha]);
    }
    return g_trie;
}

void main(int argc, char* argv[]){
    /*
        argv[1] : path to the root directory
        argv[2] : number of threads
    */

    // Stack Initialization
    Stack* stack = init_stack(argv[1]);

    // Setting number of threads 
    int num_threads = atoi(argv[2]);
    omp_set_num_threads(num_threads);

    // Initialization of Thread-level tries
    TrieNode** trie_list = init_tries(num_threads);

    // Initialization of Global Trie
    TrieNode* g_trie = get_Node();
    
    // Initialization for `get_next_file`
    int last_depth = 1;

    // Loading the stopwords
    char** list_of_words = load_stopwords();

    // Making of thread level Tries
    #pragma omp parallel default(shared) 
    {
        FileNode* pT;
        int last_doc = 0;
        FILE* doc;
        int id = omp_get_thread_num();

        // Update of Thread-Level Trie on receiving a document
        while(true){
            #pragma omp critical
            {
                pT = get_next_file(stack, last_depth);
                if(pT != NULL){
                    last_depth = pT -> depth;
                    printf("Fname: %s \n", pT->name);
                    doc = fopen(pT->name, "r");
                    if(doc == NULL){
                        perror("Can not open File");
                    }
                }
            }
            if(pT == NULL) break;
            
            process_doc(doc, trie_list[id], last_doc+1, list_of_words);
            last_doc++;
            fclose(doc);
        }
        #pragma omp barrier

        // Merging of all the Thread-Level Tries
        int i;
        #pragma omp for private(i) schedule(dynamic, 1)
        for(i = 0; i < 26; i++){
            g_trie = merge_all(g_trie, trie_list, num_threads, i);
        }
    }
}