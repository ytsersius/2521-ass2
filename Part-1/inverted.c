#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Set.h"
#include "BSTree.h"
#include "readData.h"

int main (void) {
    Set url_list = GetCollection();
    BSTree inv_idx = GetInvertedList(url_list);

    FILE *fp = fopen("invertedIndex.txt", "w+");
    BSTreeInfix(inv_idx, fp);

    freeSet(url_list);
    dropBSTree(inv_idx);
    
    fclose(fp);

    return 0;
}
