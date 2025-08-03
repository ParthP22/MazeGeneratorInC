#include "edge_list.h"

// Random Note (8/3/2025): We use the "address of" operator on each element in
// the array of Edges, because the Edge struct itself is not a pointer. Edge* list is
// the array, while list[i] is the element, so in order to pass it in as a pointer,
// we have to pass in the address of that struct by doing &(list[i]).


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
        // Store refs for list and current size of list
        Edge* list = edge_list->list;
        int curr_size = edge_list->size;

        // Add new Edge struct to the end of the list
        edge_copy(&(list[curr_size]),edge);
        edge_list->size++;
        
        // Reallocate the list if it reached max capacity
        if(edge_list->size == edge_list->capacity){
            edge_list->list = _edgelist_reallocate(edge_list);
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
        // Store refs for list and current size of list
        Edge* list = edge_list->list;
        int curr_size = edge_list->size;

        // Insert new Edge struct at index
        for(int i = curr_size; i >= index; i--){
            edge_copy(&(list[i+1]),&(list[i]));
        }
        edge_copy(&(list[index]),edge);
        edge_list->size++;

        // Reallocate the list if it reached max capacity
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
        // Store refs for list and current size of list
        Edge* list = edge_list->list;
        int curr_size = edge_list->size;

        // Remove the Edge at index
        Edge* prev_elem = &(edge_list->list[index]);
        for(int i = index; i < curr_size - 1; i++){
            edge_copy(&(list[i]),&(list[i+1]));
        }

        // Move the size pointer back by one
        free(&(list[curr_size - 1]));
        edge_list->size--;

        // Return the removed Edge
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
        // Return the Edge at index
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
        // Store ref for list
        Edge* list = edge_list->list;

        // Set the old Edge at index with the new Edge
        Edge* prev_elem = &(list[index]);
        edge_copy(&(list[index]),edge);

        // Return the old Edge that was replaced
        return prev_elem;
    }
}

int edgelist_size(EdgeList* edge_list){
    if(edge_list == NULL){
        printf("\nEdgeList is null");
        return 1/0;
    }
    else{
        // Return the current size of the list
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
    else{
        // Store refs for list and current size of list
        Edge* list = edge_list->list;
        int curr_size = edge_list->size;

        printf("\nEdgeList: \n[");
        for(int i = 0; i < curr_size - 1; i++){
            printf("[%d, %d, %d, %d, %d], \n", list[i].init_node,
                                               list[i].term_node,
                                               list[i].orientation,
                                               list[i].rand_weight,
                                               list[i].selected);
        }
        printf("[%d, %d, %d, %d, %d]]", list[edge_list->size - 1].init_node,
                                        list[edge_list->size - 1].term_node,
                                        list[edge_list->size - 1].orientation,
                                        list[edge_list->size - 1].rand_weight,
                                        list[edge_list->size - 1].selected);
    }
}

void edgelist_sort(EdgeList* edge_list) {
    if (edge_list == NULL) {
        printf("\nEdgeList is null");
        return;
    }
    else{
        qsort(edge_list->list, edge_list->size, sizeof(Edge), _compare_edges);
    }
}

int _compare_edges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->rand_weight - edgeB->rand_weight;
}

Edge* _edgelist_reallocate(EdgeList* edge_list){
    if (edge_list == NULL) {
        printf("\nEdgeList is null");
        return NULL;
    }
    else{
        // Store refs for list and current size of list
        Edge* list = edge_list->list;
        int curr_size = edge_list->size;

        // Reallocate the list
        int new_cap =  edge_list->capacity * 2;
        Edge* new_list = (Edge*)malloc(sizeof(Edge) * new_cap);
        for(int i = 0; i < curr_size; i++){
            edge_copy(&new_list[i],&(list[i]));
        }

        // Free the space for the old list
        free(list);
         
        // Update the new capacity for list
        edge_list->capacity = new_cap;

        // Return the new list
        return new_list;
    }
}