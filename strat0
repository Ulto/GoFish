#include <stdio.h>
#include <stdlib.h>

#include "gofish.h"
#include "extern.h"


/* Strategy-0
 *   randomly pick a card from the hand
 */
int Strategy0(int player)
{
    int card;

    while (1)
    {
        card = (rand() % MAXNUMB) + MINNUMB;
        if (TotalNumberOfCards(player,card) != 0)
            break;
    }
    return(card);
}
