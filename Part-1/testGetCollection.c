
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "setList.h"

Set GetCollection(void) {
    FILE *collection = fopen("collection.txt", "r");
    Set url_list = newSet();

    char temp[100];
    // Read the url IDs into a variable
    while (fscanf(collection,"%s", temp) != EOF) {
        char *url_id = malloc(strlen(temp) + 1);
        memcpy(url_id, temp, strlen(temp));
        SetInsert(url_list, url_id);
    }

    //free (url_id); // Do we need this?
    fclose(collection);

    return url_list;
}

int main()  {
    Set s = GetCollection();
    showSet(s);
    return 0;
}
