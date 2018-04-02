#include <stdio.h>
#include <stdlib.h>
#include "myHeap.h"
#include "myTrie.h"

#define INDEX_TO_CHAR(i) (char)(i + 'a')

int maxIndex(MaxHeapNode** arr, int one, int two){
	if((arr[one] -> frequency) > (arr[two] -> frequency)){
		return one;
	}else{
		return two;
	}
}

MaxHeapNode** swap(MaxHeapNode** arr, int one, int two){
	MaxHeapNode* temp = arr[one];
	arr[one] = arr[two];
	arr[two] = temp;

	return arr;
}

MaxHeapNode** maxHeapify(MaxHeapNode** arr, int last, int t){
	int L = 2 * t + 1;
	int R = 2 * t + 2;
	int mlx;

	if(L <= last){
		mlx = maxIndex(arr, L, t);
		if(R <= last){
			mlx = maxIndex(arr, R, mlx);
		}
	}else{
		mlx = t;
	}

	if(mlx != t){
		arr = swap(arr, mlx, t);
		arr = maxHeapify(arr, last, mlx);
	}
	return arr; 
}

MaxHeapNode** delete_max(MaxHeapNode** arr, int* size){
    arr[0] = arr[*size - 1];
    *size -= 1;
    arr = maxHeapify(arr, *size - 1, 0);
    return arr;
}

MaxHeapNode** buildHeap(MaxHeapNode** arr, int size){
	for(int j = size / 2; j >= 0; j--){
		arr = maxHeapify(arr, size, j);
	}
	return arr;
}

void print(MaxHeapNode** arr, int size){
	for(int i = 0; i < size; i++){
		printf("%d\t", arr[i] -> frequency);
	}
    printf("\n");
}

void print_topk(MaxHeapNode** arr, int* size, int k){
    for(int i = 0; i < k; i++){
        printf("%d : %s\n", arr[0] -> frequency, arr[0] -> word);
        arr = delete_max(arr, size);
    }
    // printf("\n");
}

MaxHeapNode** add_to_heap(TrieNode* root, MaxHeapNode** arr, int* arr_size, int* capacity, char* buffer, int iter){
	if(*arr_size >= *capacity){
		arr = (MaxHeapNode**) realloc(arr, 2 * (*capacity) * sizeof(MaxHeapNode*));
		(*capacity) *= 2;
	}
	
	arr[*arr_size] = (MaxHeapNode*) malloc(sizeof(MaxHeapNode));
	// arr[*arr_size] -> tnode = root;
    int len = strlen(buffer) + 1;
    arr[*arr_size] -> word = (char*) malloc(len * sizeof(char));
    memset(arr[*arr_size] -> word, '\0', len * sizeof(char));
    memcpy(arr[*arr_size] -> word, buffer, (len - 1) * sizeof(char));
	arr[*arr_size] -> frequency = root -> frequency;
	(*arr_size) += 1;

    return arr;
}

MaxHeapNode** make_heap_from_trie(TrieNode* root, MaxHeapNode** arr, int* arr_size, int* capacity, int alpha, char* buffer, int iter){
	if(root == NULL){
		return arr;
	}

    if(alpha != -1){
        buffer[iter] = INDEX_TO_CHAR(alpha);
    }

	if(root -> end){
		arr = add_to_heap(root, arr, arr_size, capacity, buffer, iter);
	}

	for(int i = 0; i < ALPHABET_SIZE; i++){
		if(root -> children[i] && alpha == -1){
			arr = make_heap_from_trie(root -> children[i], arr, arr_size, capacity, i, buffer, iter);
		}else if(root -> children[i]){
            arr = make_heap_from_trie(root -> children[i], arr, arr_size, capacity, i, buffer, iter + 1);
        }
	}

    if(alpha == -1){
        buffer[iter] = '\0';
    }else{
        buffer[iter + 1] = '\0';
    }

	return arr;
}

// int main(){

// 	MaxHeapNode** test = (MaxHeapNode**) malloc(10 * sizeof(MaxHeapNode*));
// 	for(int i = 0; i < 10; i++){
// 		test[i] = (MaxHeapNode*) malloc(sizeof(MaxHeapNode));
// 		test[i] -> frequency = i;
// 	}

// 	test = buildHeap(test, 9);

// 	print(test, 10	);

// 	return 0;
// }