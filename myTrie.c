#include "myTrie.h"
#include <string.h>

#define _DOC_TRIE

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

#define INDEX_TO_CHAR(i) (char)(i + 'a')

TrieNode* get_Node(void){
    TrieNode *temp = (TrieNode*) malloc(sizeof(TrieNode));
    temp -> children = (TrieNode**) malloc(ALPHABET_SIZE * sizeof(TrieNode*));
 
    if (temp){
        int i;
        temp -> end = false;
        temp -> frequency = 0;
        temp -> last_doc = -1;
        for (i = 0; i < ALPHABET_SIZE; i++){
            temp -> children[i] = NULL;
        }
    }
    return temp;
}
 
TrieNode* trie_insert(TrieNode *root, char *key, int current_doc){
    int depth, len = strlen(key), index;
 
    TrieNode *iter = root;
 
    for (depth = 0; depth < len; depth++){
        index = CHAR_TO_INDEX(key[depth]);
        if (!iter -> children[index]){
            iter -> children[index] = get_Node();
        } 
        iter = iter -> children[index];
    }

    if(current_doc != iter -> last_doc){
        iter -> frequency ++;
        iter -> end = true;
        iter -> last_doc = current_doc;
    }

    return root;
}
 
bool trie_search(struct TrieNode *root, const char *key){
    int depth, len = strlen(key), index;
    TrieNode* iter = root;
 
    for (depth = 0; depth < len; depth++){
        index = CHAR_TO_INDEX(key[depth]);
        if (!iter -> children[index]){
            return false;
        }
        iter = iter -> children[index];
    }
    printf("%d\n", iter->frequency);
    return (iter != NULL && iter -> end);
}


TrieNode* merge_trie(TrieNode *bnode, TrieNode *dnode){
    int i = 0;

    if(dnode -> end){
       bnode -> frequency += dnode -> frequency;
       bnode -> end = true;
    }
    
    for(i = 0; i < ALPHABET_SIZE; i++){
        if(dnode -> children[i]){
            if(!bnode -> children[i])
                bnode -> children[i] = get_Node();
            bnode -> children[i] = merge_trie(bnode -> children[i], dnode -> children[i]);
        }
    }
    return bnode;
}

int trie_free(TrieNode* dnode){
    int i,k=1;
    for(i=0; i< ALPHABET_SIZE; i++){
        if(dnode -> children[i])
            k += trie_free(dnode -> children[i]);
    }
    free(dnode);
    return k;
}

TrieNode* print_trie(TrieNode* root, int alpha, char* buffer, int iter){
    if(alpha != -1){
        buffer[iter] = INDEX_TO_CHAR(alpha);
    }

    if(root -> end){
        printf("%s\n", buffer);
    }

    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(root -> children[i] && alpha == -1){
            root -> children[i] = print_trie(root -> children[i], i, buffer, iter);
        }else if(root -> children[i]){
            root -> children[i] = print_trie(root -> children[i], i, buffer, iter + 1);
        }
    }

    if(alpha == -1){
        buffer[iter] = '\0';
    }else{
        buffer[iter + 1] = '\0';    
    }

    return root;
}

// int main(){
//     // Input keys (use only 'a' through 'z' and lower case)
//     char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their","the", "a", "there","the", "a", };
//     char output[][32] = {"Not present in trie", "Present in trie"};
 
//     TrieNode *root = get_doc_Node();
//     int i;
//     for (i = 0; i < ARRAY_SIZE(keys); i++){
//         doc_insert(root, keys[i]);
//     }
 
//     // Search for different keys
//     printf("%s --- %s\n", "the", output[doc_search(root, "the")] );
//     printf("%s --- %s\n", "these", output[doc_search(root, "these")] );
//     printf("%s --- %s\n", "their", output[doc_search(root, "their")] );
//     printf("%s --- %s\n", "thaw", output[doc_search(root, "thaw")] );

//     printf("%s --- %s\n", "a", output[doc_search(root, "a")] );
//     printf("%s --- %s\n", "there", output[doc_search(root, "there")] );
 
//     return 0;
// }
