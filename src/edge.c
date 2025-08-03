#include "edge.h"

bool edge_copy(Edge* dest, Edge* source){
    if(source == NULL || dest == NULL){
        return false;
    }
    else{
        dest->init_node = source->init_node;
        dest->term_node = source->term_node;
        dest->orientation = source->orientation;
        dest->rand_weight = source->rand_weight;
        dest->selected = source->selected;

        return true;
    }
    
}