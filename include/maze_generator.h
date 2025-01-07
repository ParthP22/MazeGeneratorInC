#ifndef MAZE_GENERATOR_
#define MAZE_GENERATOR_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "disjoint_set.h"
#include "edge_list.h"
#include <limits.h>

#define WIN_WIDTH 600
#define WIN_HEIGHT 600
#define UNIT_SIZE 25
#define MAZE_OFFSET 25
#define GRID_WIDTH (WIN_WIDTH - (2 * MAZE_OFFSET))/UNIT_SIZE
#define GRID_HEIGHT (WIN_HEIGHT - (2 * MAZE_OFFSET))/UNIT_SIZE

#if WIDTH_WIDTH % UNIT_SIZE != 0
#error "WIN_WIDTH must be a multiple of UNIT_SIZE"
#endif

#if WIN_HEIGHT % UNIT_SIZE != 0
#error "WIN_HEIGHT must be a multiple of UNIT_SIZE"
#endif

struct MazeGenerator{
    int (*grid)[GRID_WIDTH];
    int (*edges)[5];
    EdgeList* edge_list;
    EdgeList* mst;
}typedef MazeGenerator;

MazeGenerator* mazegenerator_init();
EdgeList* kruskals(MazeGenerator*);



#endif