
#include <stdio.h>
#include "libs/my_library.h"

int main (void) {

    int x = 14;
    int y = 12;
    printf("%d + %d = %d\n",x,y,Addition(x,y));

    return 0;
}