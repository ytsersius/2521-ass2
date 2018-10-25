#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "pageRankList.h"

int main()  {
    List L = newList();

    Vertex v = 0;
    char *url = "url11";
    float PR = 0.1245;
    ListInsert(L, v, url, PR);

     v = 1;
     url = "url11";
     PR = 0.45;
    ListInsert(L, v, url, PR);

     v = 2;
     PR = 0.534895;
    ListInsert(L, v, url, PR);

     v = 3;
     PR = 0.123;
    ListInsert(L, v, url, PR);

     v = 4;
     PR = 0.657;
    ListInsert(L, v, url, PR);

    showList(L);

    mMergeSort(L);
    //SelectionSort(L);

    showList(L);

    //freeList(L);

    return 0;
}
