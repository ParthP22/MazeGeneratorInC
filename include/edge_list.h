#ifndef EDGE_LIST_
#define EDGE_LIST_

#define DEFAULT_CAP 10

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "reallocate.h"

struct EdgeList{
    int capacity;
    int size;
    int (*arr)[2];
}typedef EdgeList;


EdgeList* edgelist_init(int);
bool edgelist_add(EdgeList*,int[2]);
bool edgelist_insert(EdgeList*,int,int[2]);
int* edgelist_remove(EdgeList*,int);
int* edgelist_get(EdgeList*,int);
int* edgelist_set(EdgeList*,int,int[2]);
int edgelist_size(EdgeList*);
bool edgelist_is_empty(EdgeList*);
void edgelist_to_string(EdgeList*);
int (*_edgelist_reallocate(EdgeList*))[2];

#endif