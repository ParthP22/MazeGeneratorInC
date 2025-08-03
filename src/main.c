#include "main.h"

int main(void)
{   

    MazeGenerator* maze_generator = mazegenerator_init();

    kruskals(maze_generator);

    EdgeList* edge_list = maze_generator->edge_list;

    // edgelist_to_string(mst);
    // edgelist_to_string(edge_list);






    

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


            //Left Border
            DrawLine((MAZE_OFFSET), (0), (MAZE_OFFSET), (GRID_HEIGHT * UNIT_SIZE + MAZE_OFFSET), BLACK);
        
            //Top Border*@
            DrawLine((MAZE_OFFSET + UNIT_SIZE), (MAZE_OFFSET), (GRID_HEIGHT * UNIT_SIZE + MAZE_OFFSET), (MAZE_OFFSET), BLACK);

            //Small Line Pointing Up Along the Top Border*@
            DrawLine((MAZE_OFFSET + UNIT_SIZE), (MAZE_OFFSET), (MAZE_OFFSET + UNIT_SIZE), (0), BLACK);
        
            //Right Border*@
            DrawLine((GRID_WIDTH * UNIT_SIZE + MAZE_OFFSET), (MAZE_OFFSET), (GRID_WIDTH * UNIT_SIZE + MAZE_OFFSET), (GRID_HEIGHT * UNIT_SIZE + (2 * MAZE_OFFSET)), BLACK);

            //Bottom Border*@
            DrawLine((MAZE_OFFSET), (GRID_HEIGHT * UNIT_SIZE + MAZE_OFFSET), (GRID_WIDTH * UNIT_SIZE + MAZE_OFFSET - UNIT_SIZE), (GRID_HEIGHT * UNIT_SIZE + MAZE_OFFSET), BLACK);


            //Small Line Pointing Down Along the Bottom Border*@
            DrawLine((GRID_WIDTH * UNIT_SIZE + MAZE_OFFSET - UNIT_SIZE), (GRID_HEIGHT * UNIT_SIZE + MAZE_OFFSET), (GRID_WIDTH * UNIT_SIZE + MAZE_OFFSET - UNIT_SIZE), (GRID_HEIGHT * UNIT_SIZE + (2 * MAZE_OFFSET)), BLACK);


            
            if (edge_list->list[i].orientation == VERTICAL) // Vertical edge
            {
            
                if (edge_list->list[i].selected == false)
                {
                    int x1 = ((edge_list->list[i].init_node % (GRID_WIDTH)) + 1) * UNIT_SIZE + MAZE_OFFSET;
                    int y1 = ((edge_list->list[i].init_node / (GRID_HEIGHT)) + 1) * UNIT_SIZE - UNIT_SIZE + MAZE_OFFSET;
                    int x2 = ((edge_list->list[i].init_node % (GRID_WIDTH)) + 1) * UNIT_SIZE + MAZE_OFFSET;
                    int y2 = ((edge_list->list[i].init_node / (GRID_HEIGHT)) + 1) * UNIT_SIZE + MAZE_OFFSET;
                    //printf("\nx1: %d, x2: %d, y1: %d, y2: %d", x1,x2,y1,y2);
                    DrawLine(x1, y1, x2, y2, BLACK);
                }

            }
            else if (edge_list->list[i].orientation == HORIZONTAL) // Horizontal edge
            {
            
                if (edge_list->list[i].selected == false)
                {
                    int x1 = ((edge_list->list[i].init_node % (GRID_WIDTH)) + 1) * UNIT_SIZE - UNIT_SIZE + MAZE_OFFSET;
                    int y1 = ((edge_list->list[i].init_node / (GRID_HEIGHT)) + 1) * UNIT_SIZE + MAZE_OFFSET;
                    int x2 = ((edge_list->list[i].init_node % (GRID_WIDTH)) + 1) * UNIT_SIZE + MAZE_OFFSET;
                    int y2 = ((edge_list->list[i].init_node / (GRID_HEIGHT)) + 1) * UNIT_SIZE + MAZE_OFFSET;
                    //printf("\nx1: %d, x2: %d, y1: %d, y2: %d", x1,x2,y1,y2);
                    DrawLine(x1, y1, x2, y2, BLACK);
                }
            }
            
        }

        //DrawText("2D Grid Example", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }
    CloseWindow();
    
    return 0;
}