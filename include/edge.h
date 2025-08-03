#ifndef EDGE_H_
#define EDGE_H_

#include <stdio.h>
#include <stdlib.h>

typedef enum Orientation{
    HORIZONTAL = 0,
    VERTICAL = 1
} Orientation;

typedef struct Edge{
    int init_node;
    int term_node;
    Orientation orientation;
    int rand_weight;
    bool selected;
} Edge;


#endif