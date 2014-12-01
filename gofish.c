#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "gofish.h"
#include "extern.h"


/* Init
 *   initializes all global structures (to zero)
 *   generates the deck
 *   calls "shuffle" to randomize the deck
 *   deals out 7 cards to each player
 */
void Init(void)
{
    int card;
    int suit;

    memset((char *)info, 0, sizeof(info));

    deck.remain = 0;
    for (suit=0; suit<MAXSUIT; suit++)
    {
        for(card=MINNUMB; card<=MAXNUMB; card++)
            deck.cards[deck.remain++] = (suit<<4) | card;
    }

    Shuffle();

    for (card=0; card<7; card++)
    {
        DrawNextCard(0);
        DrawNextCard(1);
    }
}


/* Shuffle
 *   randomizes the deck
 */
void Shuffle(void)
{
    int ofst,indx, swap;

    for (ofst=0; ofst<MAXCARD; ofst++)
    {
        indx = rand() % MAXCARD;

        swap = deck.cards[ofst];
        deck.cards[ofst] = deck.cards[indx];
        deck.cards[indx] = swap;
    }
}


/* Turn
 *   perform the players turn
 *   calls CardToAsk to determine which card to request
 *   calls TransferCard to see if there are any cards in the opponents hand
 *   calls DrawNextCard (at the end of the turn)
 */
void Turn(int player)
{
    int card;
    int total;

    while (1)
    {
        Sleep(DELAY);
        card = CardToAsk(player);
        info[player].lastcard = card;
        printf("(%s) Do you have any %s's?", info[player].name, CardNumb(card));
        total = TransferCard(player, 1-player, card);
        if (total == 0)
            break;

        Sleep(DELAY);
        printf(" ... (%s) I have %d of them\n", info[1-player].name,total);
        CheckForGroup(player, card);
        if (IsGameOver() != 0)
             break;
    }

    Sleep(DELAY);
    printf(" ... GoFish\n\n");
    DrawNextCard(player);
}


/* CardToAsk
 *   determines the next card to play
 *   calls Strategy1,2,3… to determine which card to ask
 */
int CardToAsk(int player)
{
    int card;

    switch (info[player].strategy)
    {
      case 1:  card = Strategy1(player);  break;
      case 2:  card = Strategy2(player);  break;
      case 3:  card = Strategy3(player);  break;
      case 4:  card = Strategy4(player);  break;
      //case 5:  card = Strategy5(player);  break;
      default: card = Strategy0(player);  break;
    }

    if (card < MINNUMB || card > MAXNUMB)
    {
        printf("Invalid card selection (%d)\n",card);
        //exit(1);
    }
    return(card);
}
