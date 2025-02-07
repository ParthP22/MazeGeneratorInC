#include "reallocate.h"

int* reallocate(int* arr, int rear, int front, int* capacity){
    int new_cap =  (*capacity) * 2;
    int* new_arr = (int*)malloc(sizeof(int)* new_cap);
    for(int i = rear; i < front; i++){
        new_arr[i % (*capacity)] = arr[i % (*capacity)];
    }
    free(arr);
    *capacity = new_cap;
    return new_arr;
}