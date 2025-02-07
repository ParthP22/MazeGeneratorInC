#ifndef ARRAY_HEAP_
#define ARRAY_HEAP_

#define DEFAULT_CAP 10

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "reallocate.h"

typedef struct ArrayHeap ArrayHeap;

struct ArrayHeap{
    int* heap;
    int size;
    int capacity;
};

ArrayHeap* arrheap_init();
int arrheap_parent(ArrayHeap*,int);
int arrheap_left_child(ArrayHeap*,int);
int arrheap_right_child(ArrayHeap*,int);
// void arrheap_perc_down(ArrayHeap*,int);
// void arrheap_perc_up(ArrayHeap*,int);
// void arrheap_increase_key(ArrayHeap*,int,int);
void arrheap_heapify(ArrayHeap*,int);
bool arrheap_insert(ArrayHeap*,int);
int arrheap_remove(ArrayHeap*,int);
int arrheap_extract_root(ArrayHeap*);
void arrheap_heap_sort(ArrayHeap*);
void arrheap_to_string(ArrayHeap*);
void swap(int*,int,int);

#endif