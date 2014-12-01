#include <stdio.h>
#include <string.h>
#include "gofish.h"

void SortNums(int list[MAXNUMB+1][2], int max)
{
    int ofst,swap;
    int temp;

    do
    {
       /* “swap” is used to show that a change has occurred */
        swap = 0;
        for (ofst=1; ofst<max; ofst++)
        {
            /* skip over entries that are ordered correctly */
            if (list[ofst-1][1] >= list[ofst][1])
                continue;

            /* swap the second array value entries */
            temp = list[ofst-1][1];
            list[ofst-1] [1] = list[ofst] [1];
            list[ofst][1] = temp;

            /* swap the first array value entries */
            temp = list[ofst-1][0];
            list[ofst-1] [0] = list[ofst] [0];
            list[ofst][0] = temp;

            /* and show that a change has taken place */
            swap = 1;
        }
    } while (swap != 0);
}
