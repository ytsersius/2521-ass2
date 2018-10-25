#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "setList.h"

int main()  {
    Set s = newSet();

    char *url = "url0";
    SetInsert(s, url);

    url = "url1";
    SetInsert(s, url);

    url = "url2";
    SetInsert(s, url);

    url = "url3";
    SetInsert(s, url);

    showSet(s);

    freeSet(s);

    return 0;
}
