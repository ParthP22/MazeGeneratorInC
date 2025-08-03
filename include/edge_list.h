#ifndef EDGE_LIST_
#define EDGE_LIST_

#define DEFAULT_CAP 10

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "reallocate.h"
#include "edge.h"

typedef struct EdgeList{
    int capacity;
    int size;
    int (*arr)[5];
} EdgeList;

EdgeList* edgelist_init(int);
bool edgelist_add(EdgeList*,int[5]);
bool edgelist_insert(EdgeList*,int,int[5]);
int* edgelist_remove(EdgeList*,int);
int* edgelist_get(EdgeList*,int);
int* edgelist_set(EdgeList*,int,int[5]);
int edgelist_size(EdgeList*);
bool edgelist_is_empty(EdgeList*);
void edgelist_to_string(EdgeList*);
void edgelist_sort(EdgeList* edge_list);
int _compare_edges(const void*, const void*);
int (*_edgelist_reallocate(EdgeList*))[5];

#endif