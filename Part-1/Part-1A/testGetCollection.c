
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "setList.h"

Set GetCollection(void) {
    FILE *collection = fopen("collection.txt", "r");
    Set url_list = newSet();

    char temp[100];
    // I'm not sure how to dynamically allocate memory here

    // Read the url IDs into a variable
    while (fscanf(collection,"%s", temp) != EOF) {
        char *url_id = strdup(temp);
        SetInsert(url_list, url_id);
    }

    //free (url_id); // Do we need this?
    fclose(collection);

    return url_list;
}

int main()  {
    Set s = GetCollection();
    showSet(s);
}