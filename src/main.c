#include "main.h"

int main(void)
{   


    int (*grid)[GRID_WIDTH] = (int(*)[GRID_WIDTH])malloc(sizeof(int) * GRID_HEIGHT * GRID_WIDTH);

    if(grid == NULL){
        fprintf(stderr, "Malloc for \'grid\' failed");
    }



    int (*edges)[4] = (int(*)[4])malloc(sizeof(int) * (2 * GRID_WIDTH * (GRID_WIDTH - 1)) * 4);

    if(edges == NULL){
        fprintf(stderr, "Malloc for \'edges\' failed");
    }   

    for(int i = 0, k = 0; i < GRID_HEIGHT; i++){
        for(int j = 0; j < GRID_WIDTH; j++){
            grid[i][j] = k;
            k++; 
        }
    }

    //edges[k][3] == 0, then the line is horizontal
    //edges[k][3] == 1, then the line is vertical

    for(int i = 0, k = 0; i < GRID_HEIGHT; i++){
        for(int j = 0; j < GRID_WIDTH; j++){
            if(j + 1 < GRID_WIDTH){
                edges[k][0] = grid[i][j];
                edges[k][1] = grid[i][j+1];
                edges[k][2] = 1;
                k++;
            }
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

    for(int i = 0; i < (2 * GRID_WIDTH * (GRID_WIDTH - 1)); i++){
        edges[i][3] = rand() % (max - min + 1) + min;
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
            
            djs_union(forest, initial_node, terminal_node);
        }
    }

    // edgelist_to_string(mst);






    
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "MazeGeneratorInC");
    SetTargetFPS(30);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Yuhhh", 20, 20, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
    
    return 0;
}