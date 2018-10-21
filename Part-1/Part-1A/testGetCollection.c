
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "readData.h"
#include "setList.h"

int main()  {
    Set s = GetCollection();
    showSet(s);
}