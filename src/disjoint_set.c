#include "disjoint_set.h"

void log_debug(const char *file, int line, const char *text)
{
  fprintf(stderr, "\nDEBUG '%s':%d: %s\n", file, line, text);
}

DisjointSet* djs_init(int size){
    DisjointSet* djs  = (DisjointSet*)malloc(sizeof(DisjointSet));
    djs->representatives = (int*)malloc(sizeof(int) * size);
    djs->rank = (int*)malloc(sizeof(int) * size);

    for(int i = 0; i < size; i++){
        djs->representatives[i] = i;
        djs->rank[i] = 0;
    }
    return djs;
}

int djs_find_representative(DisjointSet* djs, int num){
    if(djs == NULL){
        LOG_DEBUG("");
        exit(1);
        return num/0;
    }
    if(djs->representatives[num] == num){
        return num;
    }
    int result = djs_find_representative(djs, djs->representatives[num]);
    djs->representatives[num] = result;
    return result;
}

bool djs_union(DisjointSet* djs, int num1, int num2){
    if(djs == NULL){
        LOG_DEBUG("djs_find_representative: DisjointSet is NULL");
        exit(1);
        return false;
    }
    int num1_rep = djs_find_representative(djs, num1);
    int num2_rep = djs_find_representative(djs, num2); 
    if(num1_rep == num2_rep){
        return true;
    }
    int num1_rank = djs->rank[num1_rep];
    int num2_rank = djs->rank[num2_rep];

    if(num1_rank < num2_rank){
        djs->representatives[num1_rep] = num2_rep;
        return true;
    }
    else if(num1_rank > num2_rank){
        djs->representatives[num2_rep] = num1_rep;
        return true;
    }
    else{
        djs->representatives[num1_rep] = num2_rep;
        djs->rank[num2_rep]++;
        return true;
    }
}