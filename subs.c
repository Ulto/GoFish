#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gofish.h"
#include "extern.h"


/* TransferCard
 *   transfers all cards (of a particular number) from (src) to the other (dst)
 *   returns the number of cards that were moved (0-3)
 *   calling routine needs to check for a group of four
 */
int TransferCard(int dst, int src, int card)
{
    int total=0;
    int suit,data;

    for (suit=0; suit<MAXSUIT; suit++)
    {
        data = info[src].hand[card][suit];
        if (data != 0)
        {
            info[dst].hand[card][suit] = data;
            info[src].hand[card][suit] = 0;
            total++;
        }
    }

    /* see if the card count went to zero */
    /* and if so, draw another card */
    if (TotalCardsInHand(src) == 0)
        DrawNextCard(src);

    return(total);
}


/* CheckForGroup
 *   see if the player has a group of four of a particular card
 *   if so, move the cards out of the players hand
 *   and check to see if the hand is now empty
 */
void CheckForGroup(int player, int card)
{
    int suit;

    if (TotalNumberOfCards(player, card) != MAXSUIT)
        return;

    printf("(%s) I made a group of four %s's\n", info[player].name, CardNumb(card) );

    /* remove the cards from the hand */
    /* set a flag in "group" */
    info[player].group[card] = 1;
    for (suit=0; suit<MAXSUIT; suit++)
        info[player].hand[card][suit] = 0;

    /* see if the card count went to zero */
    /* and if so, draw another card */
    if (TotalCardsInHand(player) == 0)
        DrawNextCard(player);
}


/* DrawNextCard
 *   get the next card off the deck
 *   and check to see if we have a group of four
 */
void DrawNextCard(int player)
{
    int data,card,suit;

    if (deck.remain <= 0)
        return;

    /* we actually get the cards from the end of the deck */
    data = deck.cards[--deck.remain];

    /* convert the card to card number and suit */
    card = data & 0x0f;
    suit = (data >> 4) - HEART;

    /* add it to the players hand */
    info[player].hand[card][suit] = data;
    info[player].lastpick = card;

    CheckForGroup(player,card);
}


/* boolean test to see if the game is over */
/* no cards in the deck, no cards in either hand */
int IsGameOver(void)
{
    if (deck.remain > 0)
       return(0);

    if (TotalCardsInHand(0) > 0)
       return(0);

    if (TotalCardsInHand(1) > 0)
       return(0);

    return(1);
}


/* returns the number of cards of a particular number in the players hand */
int TotalNumberOfCards(int player, int card)
{
    int suit;
    int data=0;

    for (suit=0; suit<MAXSUIT; suit++)
    {
        if (info[player].hand[card][suit] != 0)
            data++;
    }

    return(data);
}

/* returns the total number of cards a player is holding */
int TotalCardsInHand(int player)
{
    int card;
    int suit;
    int data=0;

    for (card=MINNUMB; card<=MAXNUMB; card++)
    {
        for (suit=0; suit<MAXSUIT; suit++)
        {
           if (info[player].hand[card][suit] != 0)
              data++;
        }
    }

    return(data);
}
