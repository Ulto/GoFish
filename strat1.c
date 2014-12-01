#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "gofish.h"
#include "extern.h"

/*
 * Strategy-1
 * Assume a human player and prompt for a card
 * display error and re-prompt if the selection was invalid
 */

int Strategy1(int player)
{
    // initialize local variables
    int card = 0;
    int flag = 0;
    char text[100];

    do
    {
       // prompt player for card and read into character array
       printf("\n<%s>: Please Enter The Card You Want: ", info[player].name);
       gets_s(text, sizeof text);
       printf("\n");

       if (text[0] == 'a' || text[0] == 'A')
       {
           card = 1;
       }
       else if (text[0] == 'j' || text[0] == 'J')
       {
           card = 11;
       }
       else if (text[0] == 'q' || text[0] == 'Q')
       {
           card = 12;
       }
       else if (text[0] == 'k' || text[0] == 'K')
       {
           card = 13;
       }
       else
       {
           // convert ascii character to integer
           card = atoi(text);
       }

       // check for valid card selection and if player has at least
       // one card of that kind in their hand
       if ((card >= 1) && (card <= 13))
       {
           if (TotalNumberOfCards(player,card) != 0)
           {
               flag = 1;
           }
           else
           {
               // display error to player
               printf("\n\nYou Don't Have Any Of That Card In Your Hand!!! - Try Again...\n\n");
           }
       }
       else
       {
           // display error to player
           printf("\n\nInvalid Card Selection!!! - Try Again...\n\n");
       }
    }
    // loop until valid card is entered
    while(flag != 1);

    // return card to calling function
    return(card);
}
