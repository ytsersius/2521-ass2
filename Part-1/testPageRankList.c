#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "pageRankList.h"

int main()  {
    List L = newList();

    Vertex v = 0;
    float PR = 0.1245;
    ListInsert(L, v, PR);

     v = 1;
     PR = 0.45;
    ListInsert(L, v, PR);

     v = 2;
     PR = 0.534895;
    ListInsert(L, v, PR);

     v = 3;
     PR = 0.123;
    ListInsert(L, v, PR);

     v = 4;
     PR = 0.657;
    ListInsert(L, v, PR);

    showList(L);

    mMergeSort(L);
    //SelectionSort(L);

    showList(L);

    freeList(L);

    return 0;
}
