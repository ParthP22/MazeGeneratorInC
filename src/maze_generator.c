#include "maze_generator.h"

// Initialize MazeGenerator
MazeGenerator* mazegenerator_init(){
    // Malloc MazeGenerator struct
    MazeGenerator* maze_generator = (MazeGenerator*)malloc(sizeof(MazeGenerator));

    // Grid is initialized with size m*n
    maze_generator->grid = (int(*)[GRID_WIDTH])malloc(sizeof(int) * GRID_HEIGHT * GRID_WIDTH);
    if(maze_generator->grid == NULL){
        fprintf(stderr, "Malloc for \'grid\' failed");
    }

    // Initializes an array with 2*n*(n-1) Edges (which is the number of edges in a grid)
    maze_generator->edges = (Edge*)malloc(sizeof(Edge) * (2 * GRID_WIDTH * (GRID_WIDTH - 1)));
    if(maze_generator->edges == NULL){
        fprintf(stderr, "Malloc for \'edges\' failed");
    }   

    // Store refs for grid and edges
    int (*grid)[GRID_WIDTH] = maze_generator->grid;
    Edge* edges = maze_generator->edges;


    // Each node in the grid is numbered 0 to (n*n)-1
    for(int i = 0, k = 0; i < GRID_HEIGHT; i++){
        for(int j = 0; j < GRID_WIDTH; j++){
            grid[i][j] = k;
            k++; 
        }
    }

    // Set the initial and terminal nodes of each edge, as well as 
    // defining of the orientation of the edge (A maze will have either 
    // horizontal or vertical edges)
    for(int i = 0, k = 0; i < GRID_HEIGHT; i++){
        for(int j = 0; j < GRID_WIDTH; j++){
            // Determines if the edge exists and if it will be drawn as a vertical line
            if(j + 1 < GRID_WIDTH){
                edges[k].init_node = grid[i][j];
                edges[k].term_node = grid[i][j+1];
                edges[k].orientation = VERTICAL;
                k++;
            }
            // Determines if the edge exists and if it will be drawn as a horizontal line
            if(i + 1 < GRID_HEIGHT){
                edges[k].init_node = grid[i][j];
                edges[k].term_node = grid[i+1][j];
                edges[k].orientation = HORIZONTAL;
                k++;
            }
        }
    }

    // Initialize random number generator
    srand(time(NULL));

    // Bounds for a random number between 1 and (2^31)-1
    int min = 1;
    int max = INT_MAX;

    // Sets a random weight for every edge
    for(int i = 0; i < (2 * GRID_WIDTH * (GRID_WIDTH - 1)); i++){
        edges[i].rand_weight = rand() % (max - min + 1) + min;
        edges[i].selected = false;
    }

    // Initialize EdgeList with size 2*n*(n-1)
    maze_generator->edge_list = edgelist_init((2 * GRID_WIDTH * (GRID_WIDTH - 1)));
    if(maze_generator->edge_list == NULL){
        fprintf(stderr, "Malloc for \'edge_list\' failed");
    }

    // Store ref for edge list
    EdgeList* edge_list = maze_generator->edge_list;

    // Add all Edges from the edges array into the edge list
    for(int i = 0; i < (2 * GRID_WIDTH * (GRID_WIDTH - 1)); i++){
        edgelist_add(edge_list, &edges[i]);
    }

    return maze_generator;
}

// Kruskal's algorithm to find Minimum Spanning Tree in a graph
EdgeList* kruskals(MazeGenerator* maze_generator){
    // Create Disjoint Set to perform Union Find operations for Kruskal's algo
    DisjointSet* forest = djs_init(GRID_WIDTH * GRID_WIDTH);
    if(forest == NULL){
        fprintf(stderr, "Malloc for \'forest\' failed");
    }

    // Initialize the edge_list for the Minimum Spanning Tree
    maze_generator->mst = edgelist_init(GRID_WIDTH - 1);
    if(maze_generator->edge_list == NULL){
        fprintf(stderr, "Malloc for \'edge_list\' failed");
    }

    // Store refs for edge list, edge list size, and minimum spanning tree
    EdgeList* edge_list = maze_generator->edge_list;
    int size = edgelist_size(edge_list);
    EdgeList* mst = maze_generator->mst;

    // Sort all edges in this list in ascending order
    edgelist_sort(edge_list);    

    // Perform Kruskal's Algorithm to find Minimum Spanning Tree of a graph
    for(int i = 0; i < size; i++){
        Edge* node = edgelist_get(edge_list,i);
        if(node == NULL){
            break;
        }
        int initial_node = djs_find_representative(forest, node->init_node);
        int terminal_node = djs_find_representative(forest, node->term_node);
        
        if(initial_node != terminal_node){
            Edge* tmp = edgelist_get(edge_list,i);
            if(tmp == NULL){
                printf("Tmp is NULL, index: %d", i);
            }
            edgelist_add(mst, tmp);

            edge_list->list[i].selected = true;
            
            djs_union(forest, initial_node, terminal_node);
        }
    }

    // Return the Minimum Spanning Tree found by the algo above
    return mst;
}