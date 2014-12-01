#include <stdio.h>

#include "gofish.h"
#include "extern.h"

/* Strategy-2
 *   sequentially step through each card in the hand
 *   starting at ace (card-1) see if this is in the hand, if so ask, if not, go to the next
 *   each time through, pick up where you left off
 *   need a static variable to keep track (static int last[2])
 *   and use "player" to index into the array
 */
int Strategy2(int player)
{
    int card;
    // ... put code here ...

    return(card);
}
