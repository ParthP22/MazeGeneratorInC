#include "edge_list.h"

EdgeList* edgelist_init(int capacity){
    EdgeList* edge_list = (EdgeList*)malloc(sizeof(EdgeList));
    edge_list->list = (Edge*)malloc(sizeof(Edge) * capacity);
    edge_list->capacity = capacity;
    edge_list->size = 0;
    return edge_list;
}

bool edgelist_add(EdgeList* edge_list, Edge* edge){
    if(edge_list == NULL){
        printf("\nEdgeList is null");
        return false;
    }
    else{
        int curr_size = edge_list->size;
        edge_copy(&(edge_list->list[curr_size]),edge);
        edge_list->size++;
        if(edge_list->size == edge_list->capacity){
            edge_list->list = _edgelist_reallocate(edge_list);
            //printf("Realloc...");
        }
        return true;
    }
}

bool edgelist_insert(EdgeList* edge_list, int index, Edge* edge){
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
            edge_copy(&(edge_list->list[i+1]),&(edge_list->list[i]));
        }
        edge_copy(&(edge_list->list[index]),edge);
        edge_list->size++;
        if(edge_list->size == edge_list->capacity){
            edge_list->list = _edgelist_reallocate(edge_list);
        }
        return true;
    }

}

Edge* edgelist_remove(EdgeList* edge_list, int index){
    if(edge_list == NULL){
        printf("\nEdgeList is null");
        return NULL;
    }
    else if(index > edge_list->size - 1 || index < 0){
        printf("\nIndex is out of bounds for index: %d",index);
        return NULL;
    }
    else{
        Edge* prev_elem = &(edge_list->list[index]);
        for(int i = index; i < edge_list->size - 1; i++){
            edge_copy(&(edge_list->list[i]),&(edge_list->list[i+1]));
        }
        free(&(edge_list->list[edge_list->size - 1]));
        
        edge_list->size--;
        return prev_elem;
    }
}

Edge* edgelist_get(EdgeList* edge_list, int index){
    if(edge_list == NULL){
        printf("\nEdgeList is null");
        return NULL;
    }
    else if(index >= edge_list->size || index < 0){
        printf("\nIndex is out of bounds for index: %d",index);
        return NULL;
    }
    else{
        return &(edge_list->list[index]);
    }
}

Edge* edgelist_set(EdgeList* edge_list, int index, Edge* edge){
    if(edge_list == NULL){
        printf("\nEdgeList is null");
        return NULL;
    }
    else if(index > edge_list->size || index < 0){
        printf("\nIndex is out of bounds for index: %d",index);
        return NULL;
    }
    else{
        Edge* prev_elem = &(edge_list->list[index]);
        edge_copy(&(edge_list->list[index]),edge);
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
        printf("[%d, %d, %d, %d, %d], \n", edge_list->list[i].init_node,
                                           edge_list->list[i].term_node,
                                           edge_list->list[i].orientation,
                                           edge_list->list[i].rand_weight,
                                           edge_list->list[i].selected);
    }
    printf("[%d, %d, %d, %d, %d], \n", edge_list->list[edge_list->size - 1].init_node,
                                       edge_list->list[edge_list->size - 1].term_node,
                                       edge_list->list[edge_list->size - 1].orientation,
                                       edge_list->list[edge_list->size - 1].rand_weight,
                                       edge_list->list[edge_list->size - 1].selected);
    
}

void edgelist_sort(EdgeList* edge_list) {
    if (edge_list == NULL) {
        printf("\nEdgeList is null");
        return;
    }
    qsort(edge_list->list, edge_list->size, sizeof(Edge), _compare_edges);
}

int _compare_edges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->rand_weight - edgeB->rand_weight;
}

Edge* _edgelist_reallocate(EdgeList* edge_list){
    int new_cap =  edge_list->capacity * 2;
    Edge* new_list = (Edge*)malloc(sizeof(Edge) * new_cap);
    for(int i = 0; i < edge_list->size; i++){
        edge_copy(&new_list[i],&(edge_list->list[i]));
    }
    free(edge_list->list);
    edge_list->capacity = new_cap;
    return new_list;
}