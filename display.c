#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gofish.h"
#include "extern.h"


/* ShowAll
 *   displays the cards that are in each players hand
 *   displays the 4-card grouping for each player
 *   shows the total number of cards remaining in the deck
 */
void ShowAll(void)
{
    ShowHand(0);
    ShowGroups(0);
    ShowHand(1);
    ShowGroups(1);
    ShowDeck();
}


void ShowHand(int player)
{
    int card,suit;
    int data;

    printf("%s:\n",info[player].name);
    printf("  Cards:  ");
    for (card=MINNUMB; card<=MAXNUMB; card++)
    {
        for (suit=0; suit<MAXSUIT; suit++)
        {
            data = info[player].hand[card][suit];
            if (data != 0)
                printf(" %s-%c", CardNumb(data&0x0f), 3 + (data >> 4));
        }
    }
    printf("\n");
}


void ShowGroups(int player)
{
    int card;
    int total=0;

    printf("  Groups: ");
    for (card=MINNUMB; card<=MAXNUMB; card++)
    {
        if (info[player].group[card] != 0)
        {
            total++;
            printf(" %s", CardNumb(card));
        }
    }
    printf(" (%d groups)\n",total);
}


void ShowDeck(void)
{
    printf("%d cards remaining in the deck\n\n",deck.remain);
}


/* CardNumb
 *   converts the card number to its text name
 */
char *CardNumb(int card)
{
    switch (card)
    {
      case  1: return("Ace");
      case  2: return("2");
      case  3: return("3");
      case  4: return("4");
      case  5: return("5");
      case  6: return("6");
      case  7: return("7");
      case  8: return("8");
      case  9: return("9");
      case 10: return("10");
      case 11: return("Jack");
      case 12: return("Queen");
      case 13: return("King");
    }
    return("");
}
