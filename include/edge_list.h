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
    Edge* list;
} EdgeList;

EdgeList* edgelist_init(int);
bool edgelist_add(EdgeList*,Edge*);
bool edgelist_insert(EdgeList*,int,Edge*);
Edge* edgelist_remove(EdgeList*,int);
Edge* edgelist_get(EdgeList*,int);
Edge* edgelist_set(EdgeList*,int,Edge*);
int edgelist_size(EdgeList*);
bool edgelist_is_empty(EdgeList*);
void edgelist_to_string(EdgeList*);
void edgelist_sort(EdgeList* edge_list);
int _compare_edges(const void*, const void*);
Edge* _edgelist_reallocate(EdgeList*);

#endif