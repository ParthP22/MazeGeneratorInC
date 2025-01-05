#include "edge_list.h"

EdgeList* edgelist_init(int capacity){
    EdgeList* edge_list = (EdgeList*)malloc(sizeof(EdgeList));
    edge_list->arr = (int(*)[5])malloc(sizeof(int)* 5 * capacity);
    edge_list->capacity = capacity;
    edge_list->size = 0;
    return edge_list;
}

bool edgelist_add(EdgeList* edge_list, int edge[5]){
    if(edge_list == NULL){
        printf("\nEdgeList is null");
        return false;
    }
    else{
        edge_list->arr[edge_list->size][0] = edge[0];
        edge_list->arr[edge_list->size][1] = edge[1];
        edge_list->arr[edge_list->size][2] = edge[2];
        edge_list->arr[edge_list->size][3] = edge[3];
        edge_list->arr[edge_list->size][4] = edge[4];
        edge_list->size++;
        if(edge_list->size == edge_list->capacity){
            edge_list->arr = _edgelist_reallocate(edge_list);
            //printf("Realloc...");
        }
        return true;
    }
}

bool edgelist_insert(EdgeList* edge_list, int index, int edge[5]){
    if(edge_list == NULL){
        printf("\nEdgeList is null");
        return false;
    }
    else if(index > edge_list->size || index < 0){
        printf("\nIndex is out of bounds for index: %d",index);
        return false;
    }
    else{
        for(int i = edge_list->size; i >= index; i--){
            edge_list->arr[i+1][0] = edge_list->arr[i][0];
            edge_list->arr[i+1][1] = edge_list->arr[i][1];
            edge_list->arr[i+1][2] = edge_list->arr[i][2];
            edge_list->arr[i+1][3] = edge_list->arr[i][3];
            edge_list->arr[i+1][4] = edge_list->arr[i][4];
        }
        edge_list->arr[index][0] = edge[0];
        edge_list->arr[index][1] = edge[1];
        edge_list->arr[index][2] = edge[2];
        edge_list->arr[index][3] = edge[3];
        edge_list->arr[index][4] = edge[4];
        edge_list->size++;
        if(edge_list->size == edge_list->capacity){
            edge_list->arr = _edgelist_reallocate(edge_list);
        }
        return true;
    }

}

int* edgelist_remove(EdgeList* edge_list, int index){
    if(edge_list == NULL){
        printf("\nEdgeList is null");
        return NULL;
    }
    else if(index > edge_list->size - 1 || index < 0){
        printf("\nIndex is out of bounds for index: %d",index);
        return NULL;
    }
    else{
        int* prev_elem = edge_list->arr[index];
        for(int i = index; i < edge_list->size - 1; i++){
            edge_list->arr[i][0] = edge_list->arr[i+1][0];
            edge_list->arr[i][1] = edge_list->arr[i+1][1];
            edge_list->arr[i][2] = edge_list->arr[i+1][2];
            edge_list->arr[i][3] = edge_list->arr[i+1][3];
            edge_list->arr[i][4] = edge_list->arr[i+1][4];
        }
        edge_list->arr[edge_list->size - 1][0] = 0;
        edge_list->arr[edge_list->size - 1][1] = 0;
        edge_list->arr[edge_list->size - 1][2] = 0;
        edge_list->arr[edge_list->size - 1][3] = 0;
        edge_list->arr[edge_list->size - 1][4] = 0;
        edge_list->size--;
        return prev_elem;
    }
}

int* edgelist_get(EdgeList* edge_list, int index){
    if(edge_list == NULL){
        printf("\nEdgeList is null");
        return NULL;
    }
    else if(index >= edge_list->size || index < 0){
        printf("\nIndex is out of bounds for index: %d",index);
        return NULL;
    }
    else{
        return edge_list->arr[index];
    }
}

int* edgelist_set(EdgeList* edge_list, int index, int edge[5]){
    if(edge_list == NULL){
        printf("\nEdgeList is null");
        return NULL;
    }
    else if(index > edge_list->size || index < 0){
        printf("\nIndex is out of bounds for index: %d",index);
        return NULL;
    }
    else{
        int* prev_elem = edge_list->arr[index];
        edge_list->arr[index][0] = edge[0];
        edge_list->arr[index][1] = edge[1];
        edge_list->arr[index][2] = edge[2];
        edge_list->arr[index][3] = edge[3];
        edge_list->arr[index][4] = edge[4];
        return prev_elem;
    }
}

int edgelist_size(EdgeList* edge_list){
    if(edge_list == NULL){
        printf("\nEdgeList is null");
        return 1/0;
    }
    else{
        return edge_list->size;
    }
}

bool edgelist_is_empty(EdgeList* edge_list){
    if(edge_list == NULL){
        printf("\nEdgeList is null");
        return true;
    }
    else if(edge_list->size == 0){
        return true;
    }
    else{
        return false;
    }
}

void edgelist_to_string(EdgeList* edge_list){
    if(edge_list == NULL){
        printf("\nEdgeList is null");
        return;
    }
    printf("\nEdgeList: \n[");
    for(int i = 0; i < edge_list->size - 1; i++){
        printf("[%d, %d, %d, %d, %d], \n", edge_list->arr[i][0],
                                       edge_list->arr[i][1],
                                       edge_list->arr[i][2],
                                       edge_list->arr[i][3],
                                       edge_list->arr[i][4]);
    }
    printf("[%d, %d, %d, %d, %d]]", edge_list->arr[edge_list->size - 1][0],
                                edge_list->arr[edge_list->size - 1][1],
                                edge_list->arr[edge_list->size - 1][2],
                                edge_list->arr[edge_list->size - 1][3],
                                edge_list->arr[edge_list->size - 1][4]);
}

void edgelist_sort(EdgeList* edge_list) {
    if (edge_list == NULL) {
        printf("\nEdgeList is null");
        return;
    }
    qsort(edge_list->arr, edge_list->size, sizeof(edge_list->arr[0]), _compare_edges);
}

int _compare_edges(const void* a, const void* b) {
    int (*pairA)[5] = (int(*)[5])a;
    int (*pairB)[5] = (int(*)[5])b;
    return (*pairA)[3] - (*pairB)[3]; // Compare based on the first element of the pairs
}

int (*_edgelist_reallocate(EdgeList* edge_list))[5]{
    int new_cap =  edge_list->capacity * 2;
    int (*new_arr)[5] = (int(*)[5])malloc(sizeof(int) * new_cap * 5);
    for(int i = 0; i < edge_list->size; i++){
        new_arr[i][0] = edge_list->arr[i][0];
        new_arr[i][1] = edge_list->arr[i][1];
        new_arr[i][2] = edge_list->arr[i][2];
        new_arr[i][3] = edge_list->arr[i][3];
        new_arr[i][4] = edge_list->arr[i][4];
    }
    free(edge_list->arr);
    edge_list->capacity = new_cap;
    return new_arr;
}