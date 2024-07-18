#ifndef DISJOINT_SET_
#define DISJOINT_SET_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#define LOG_DEBUG(TEXT) log_debug(__FILE__, __LINE__, TEXT)

typedef struct DisjointSet DisjointSet;

struct DisjointSet{
    int* representatives;
    int* rank;
};

DisjointSet* djs_init(int);
int djs_find_representative(DisjointSet*,int);
bool djs_union(DisjointSet*,int,int);


#endif