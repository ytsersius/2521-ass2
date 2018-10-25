#ifndef PAGERANKLIST_H
#define PAGERANKLIST_H

#include <stdbool.h>

typedef struct ListRep *List;
typedef int Vertex;
typedef struct Node {
    Vertex vID;
    float PR;
    struct Node *next;
} Node;



List newList(void);   //create new List

void freeList(List);  //free List memory

void ListInsert(List, Vertex, float);   //add value into List

void ListDelete(List, Vertex);    //remove value from List

void showList(List);

void SelectionSort(List);

void mMergeSort(List);

#endif