#ifndef PAGERANKList_H
#define PAGERANKList_H

#include <stdbool.h>
typedef int Vertex;


typedef struct PRNode {
    Vertex vID;
    char *url;
    float PR;
    struct PRNode *next;
} PRNode;

struct PRListRep {
	int     nelems;
    PRNode    *elems;
};

typedef struct PRListRep *PRList;






PRList newList(void);   //create new List

void freeList(PRList);  //free List memory

void ListInsert(PRList, Vertex, char *, float);   //add value into List

void ListDelete(PRList, Vertex);    //remove value from List

void showList(PRList);

void SelectionSort(PRList);

void mMergeSort(PRList);

#endif