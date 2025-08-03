#include "main.h"

int main(void)
{   
    // Initialize Maze Generator
    MazeGenerator* maze_generator = mazegenerator_init();

    // Run Kruskal's algorithm
    kruskals(maze_generator);

    // Store ref for list of edges and size
    Edge* list = maze_generator->edge_list->list;
    int size = maze_generator->edge_list->size;

    // Initialize window using raylib
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "MazeGeneratorInC");
    SetTargetFPS(30);
    while (!WindowShouldClose()) {
        BeginDrawing();

        // Set background to white
        ClearBackground(RAYWHITE);

        // Iterate through the list of edges and draw them if they weren't selected to be in the Minimum Spanning Tree
        for(int i = 0; i < size; i++){

            // Left Border
            DrawLine((MAZE_OFFSET), (0), (MAZE_OFFSET), (GRID_HEIGHT * UNIT_SIZE + MAZE_OFFSET), BLACK);
        
            // Top Border
            DrawLine((MAZE_OFFSET + UNIT_SIZE), (MAZE_OFFSET), (GRID_HEIGHT * UNIT_SIZE + MAZE_OFFSET), (MAZE_OFFSET), BLACK);

            // Small Line Pointing Up Along the Top Border
            DrawLine((MAZE_OFFSET + UNIT_SIZE), (MAZE_OFFSET), (MAZE_OFFSET + UNIT_SIZE), (0), BLACK);
        
            // Right Border
            DrawLine((GRID_WIDTH * UNIT_SIZE + MAZE_OFFSET), (MAZE_OFFSET), (GRID_WIDTH * UNIT_SIZE + MAZE_OFFSET), (GRID_HEIGHT * UNIT_SIZE + (2 * MAZE_OFFSET)), BLACK);

            // Bottom Border
            DrawLine((MAZE_OFFSET), (GRID_HEIGHT * UNIT_SIZE + MAZE_OFFSET), (GRID_WIDTH * UNIT_SIZE + MAZE_OFFSET - UNIT_SIZE), (GRID_HEIGHT * UNIT_SIZE + MAZE_OFFSET), BLACK);


            // Small Line Pointing Down Along the Bottom Border
            DrawLine((GRID_WIDTH * UNIT_SIZE + MAZE_OFFSET - UNIT_SIZE), (GRID_HEIGHT * UNIT_SIZE + MAZE_OFFSET), (GRID_WIDTH * UNIT_SIZE + MAZE_OFFSET - UNIT_SIZE), (GRID_HEIGHT * UNIT_SIZE + (2 * MAZE_OFFSET)), BLACK);

            // If the edge wasn't in the Minimum Spanning Tree, then draw it
            if (list[i].selected == false)
            {
                // Draw vertical edge
                if (list[i].orientation == VERTICAL)
                {
                    int x1 = ((list[i].init_node % (GRID_WIDTH)) + 1) * UNIT_SIZE + MAZE_OFFSET;
                    int y1 = ((list[i].init_node / (GRID_HEIGHT)) + 1) * UNIT_SIZE - UNIT_SIZE + MAZE_OFFSET;
                    int x2 = ((list[i].init_node % (GRID_WIDTH)) + 1) * UNIT_SIZE + MAZE_OFFSET;
                    int y2 = ((list[i].init_node / (GRID_HEIGHT)) + 1) * UNIT_SIZE + MAZE_OFFSET;
                    DrawLine(x1, y1, x2, y2, BLACK);
                }
                // Draw horizontal edge
                else if (list[i].orientation == HORIZONTAL)
                {
                    int x1 = ((list[i].init_node % (GRID_WIDTH)) + 1) * UNIT_SIZE - UNIT_SIZE + MAZE_OFFSET;
                    int y1 = ((list[i].init_node / (GRID_HEIGHT)) + 1) * UNIT_SIZE + MAZE_OFFSET;
                    int x2 = ((list[i].init_node % (GRID_WIDTH)) + 1) * UNIT_SIZE + MAZE_OFFSET;
                    int y2 = ((list[i].init_node / (GRID_HEIGHT)) + 1) * UNIT_SIZE + MAZE_OFFSET;
                    DrawLine(x1, y1, x2, y2, BLACK);
                    
                }
            }
            
            
            
        }
        EndDrawing();
    }
    CloseWindow();
    
    return 0;
}