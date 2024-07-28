#include "main.h"

int main(void)
{   


    int (*grid)[GRID_WIDTH] = (int(*)[GRID_WIDTH])malloc(sizeof(int) * GRID_HEIGHT * GRID_WIDTH);

    if(grid == NULL){
        fprintf(stderr, "Malloc for \'grid\' failed");
    }



    int (*edge_list)[2] = (int(*)[2])malloc(sizeof(int) * (2 * GRID_WIDTH * (GRID_WIDTH - 1)) * 2);

    if(edge_list == NULL){
        fprintf(stderr, "Malloc for \'edge_list\' failed");
    }   

    for(int i = 0, k = 1; i < GRID_HEIGHT; i++){
        for(int j = 0; j < GRID_WIDTH; j++){
            grid[i][j] = k;
            k++; 
        }
    }

    for(int i = 0, k = 0; i < GRID_HEIGHT; i++){
        for(int j = 0; j < GRID_WIDTH; j++){
            if(j + 1 < GRID_WIDTH){
                edge_list[k][0] = grid[i][j];
                edge_list[k][1] = grid[i][j+1];
                k++;
            }
            if(i + 1 < GRID_HEIGHT){
                edge_list[k][0] = grid[i][j];
                edge_list[k][1] = grid[i+1][j];
                k++;
            }
        }
    }

    printf("Nodes: [");
    for(int i = 0; i < GRID_HEIGHT; i++){
        for(int j = 0; j < GRID_WIDTH; j++){
            printf("%d, ", grid[i][j]);
        }
    }
    printf("]");

    printf("\nEdges: [");
    for(int i = 0; i < (2 * GRID_WIDTH * (GRID_WIDTH - 1)); i++){
        printf("[%d, %d], ", edge_list[i][0], edge_list[i][1]);
        
    }
    printf("]");



    
    // GLFWwindow* window;
    // DisjointSet* djs = djs_init(GRID_WIDTH * GRID_HEIGHT);
    // /* Initialize the library */
    // if (!glfwInit())
    //     return -1;

    // /* Create a windowed mode window and its OpenGL context */
    // window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Maze Generator", NULL, NULL);
    // if (!window)
    // {
    //     glfwTerminate();
    //     return -1;
    // }

    // /* Make the window's context current */
    // glfwMakeContextCurrent(window);

	// if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // {
    //     printf("Failed to initialize GLAD\n");
    //     return -1;
    // }

    // /* Loop until the user closes the window */
    // while (!glfwWindowShouldClose(window))
    // {
    //     /* Render here */
    //     glClear(GL_COLOR_BUFFER_BIT);

    //     /* Swap front and back buffers */
    //     glfwSwapBuffers(window);

    //     /* Poll for and process events */
    //     glfwPollEvents();
    // }

    // glfwTerminate();
    
    return 0;
}