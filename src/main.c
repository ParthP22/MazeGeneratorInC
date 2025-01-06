#include "main.h"

int main(void)
{   

    //Grid is initialized with size n*n
    int (*grid)[GRID_WIDTH] = (int(*)[GRID_WIDTH])malloc(sizeof(int) * GRID_HEIGHT * GRID_WIDTH);

    if(grid == NULL){
        fprintf(stderr, "Malloc for \'grid\' failed");
    }


    //initializes a 2D matrix with 2*n*(n-1) rows (which is the number of edges in a grid) and
    //4 columns for each row.
    int (*edges)[5] = (int(*)[5])malloc(sizeof(int) * (2 * GRID_WIDTH * (GRID_WIDTH - 1)) * 5);

    if(edges == NULL){
        fprintf(stderr, "Malloc for \'edges\' failed");
    }   

    //Each node in the grid is numbered 0 to (n*n) - 1
    for(int i = 0, k = 0; i < GRID_HEIGHT; i++){
        for(int j = 0; j < GRID_WIDTH; j++){
            grid[i][j] = k;
            k++; 
        }
    }

    //edges[k][2] == 0, then the line is horizontal
    //edges[k][2] == 1, then the line is vertical
    //k is referring to the node in the grid (numbered from 0,...,n*n)
    //edges[k][0] is the initial node of the edge, and edges[k][1] is the terminal node
    for(int i = 0, k = 0; i < GRID_HEIGHT; i++){
        for(int j = 0; j < GRID_WIDTH; j++){
            //determines of the edge exists and if it will be drawn as a vertical line
            if(j + 1 < GRID_WIDTH){
                edges[k][0] = grid[i][j];
                edges[k][1] = grid[i][j+1];
                edges[k][2] = 1;
                k++;
            }
            //determines of the edge exists and if it will be drawn as a horizontal line
            if(i + 1 < GRID_HEIGHT){
                edges[k][0] = grid[i][j];
                edges[k][1] = grid[i+1][j];
                edges[k][2] = 0;
                k++;
            }
        }
    }

    srand(time(NULL));

    // Generate a random number between 0 and RAND_MAX
    int random_number = rand();
    printf("Random number (0 to RAND_MAX): %d\n", random_number);

    // Generate a random number between 1 and 100
    int min = 1;
    int max = INT_MAX;

    // Sets a random weight for every edge
    for(int i = 0; i < (2 * GRID_WIDTH * (GRID_WIDTH - 1)); i++){
        edges[i][3] = rand() % (max - min + 1) + min;
        edges[i][4] = 1;
    }



    // printf("Nodes: [");
    // for(int i = 0; i < GRID_HEIGHT; i++){
    //     for(int j = 0; j < GRID_WIDTH; j++){
    //         printf("%d, ", grid[i][j]);
    //     }
    // }
    // printf("]");

    EdgeList* edge_list = edgelist_init((2 * GRID_WIDTH * (GRID_WIDTH - 1)));

    printf("\nEdges: [");
    for(int i = 0; i < (2 * GRID_WIDTH * (GRID_WIDTH - 1)); i++){
        printf("[%d, %d], ", edges[i][0], edges[i][1]);
        edgelist_add(edge_list, edges[i]);
    }
    printf("]");

    edgelist_sort(edge_list);

    // edgelist_to_string(edge_list);

    DisjointSet* forest = djs_init(GRID_WIDTH * GRID_WIDTH);
    int size = edgelist_size(edge_list);
    // printf("Print: %d", size);

    EdgeList* mst = edgelist_init(GRID_WIDTH - 1);
    // int* tmp = edgelist_get(edge_list,0);
    // printf("Print %d, ", tmp[0]);

    for(int i = 0; i < size; i++){
        int* node = edgelist_get(edge_list,i);
        if(node == NULL){
            // printf("Initial Index: %d", i);
            break;
        }
        //printf("\nIndex: %d", i);
        int initial_node = djs_find_representative(forest, node[0]);
        int terminal_node = djs_find_representative(forest, node[1]);
        
        if(initial_node != terminal_node){
            int* tmp = edgelist_get(edge_list,i);
            if(tmp == NULL){
                printf("Tmp is NULL, index: %d", i);
            }
            edgelist_add(mst, tmp);

            edge_list->arr[i][4] = 0;
            
            djs_union(forest, initial_node, terminal_node);
        }
    }

    // edgelist_to_string(mst);
    edgelist_to_string(edge_list);






    

    InitWindow(WIN_WIDTH, WIN_HEIGHT, "MazeGeneratorInC");
    SetTargetFPS(30);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // for (int x = 0; x <= WIN_WIDTH; x += UNIT_SIZE)
        // {
        //     DrawLine(x, 0, x, WIN_HEIGHT, LIGHTGRAY); // Vertical lines
        // }
        // for (int y = 0; y <= WIN_HEIGHT; y += UNIT_SIZE)
        // {
        //     DrawLine(0, y, WIN_WIDTH, y, LIGHTGRAY); // Horizontal lines
        //}
        for(int i = 0; i < edge_list->size; i++){

            if (edge_list->arr[i][2] == 1) // Vertical edge
            {
            
                if (edge_list->arr[i][4] == 1)
                {
                    int x1 = ((edge_list->arr[i][0] % (GRID_WIDTH)) + 1) * UNIT_SIZE;// + MAZE_OFFSET;
                    int y1 = ((edge_list->arr[i][0] / (GRID_HEIGHT)) + 1) * UNIT_SIZE - UNIT_SIZE;// + MAZE_OFFSET;
                    int x2 = ((edge_list->arr[i][0] % (GRID_WIDTH)) + 1) * UNIT_SIZE;// + MAZE_OFFSET;
                    int y2 = ((edge_list->arr[i][0] / (GRID_HEIGHT)) + 1) * UNIT_SIZE;// + MAZE_OFFSET;
                    //printf("\nx1: %d, x2: %d, y1: %d, y2: %d", x1,x2,y1,y2);
                    DrawLine(x1, y1, x2, y2, LIGHTGRAY);
                }

            }
            else if (edge_list->arr[i][2] == 0) // Horizontal edge
            {
            
                if (edge_list->arr[i][4] == 1)
                {
                    int x1 = ((edge_list->arr[i][0] % (GRID_WIDTH)) + 1) * UNIT_SIZE - UNIT_SIZE;// + MAZE_OFFSET;
                    int y1 = ((edge_list->arr[i][0] / (GRID_HEIGHT)) + 1) * UNIT_SIZE;// + MAZE_OFFSET;
                    int x2 = ((edge_list->arr[i][0] % (GRID_WIDTH)) + 1) * UNIT_SIZE;// + MAZE_OFFSET;
                    int y2 = ((edge_list->arr[i][0] / (GRID_HEIGHT)) + 1) * UNIT_SIZE;// + MAZE_OFFSET;
                    //printf("\nx1: %d, x2: %d, y1: %d, y2: %d", x1,x2,y1,y2);
                    DrawLine(x1, y1, x2, y2, LIGHTGRAY);
                }
            }
        }

        //DrawText("2D Grid Example", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }
    CloseWindow();
    
    return 0;
}