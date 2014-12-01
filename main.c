#if 0
This is the game of Go-Fish.  The goal is to acquire groups of
four cards, where each group is composed of all four suits
(spades, hearts, diamond and clubs) of the same number card.

On your turn, you can ask for any card, provided that you are
holding at least one card (of that number) in your hand.
The way you ask is by typing in the number of the card
(2 to 10, or J, Q, K or A) and then press the Enter key.

If the second player has any of that number, he must give you
all of them and you get another turn.  If he has none, he will
respond by saying Go-Fish and you get to pick from the draw pile.

Once you have a grouping of four, you take the cards out of your
hand.  If this results in you having no cards (in your hand),
then you take a card from the draw pile and continue.

The game begins with each player getting 7 cards.

The game ends when there is no cards left in either hand, and the
draw pile is also empty.  The player with the most groups of four
wins.
#endif


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "gofish.h"

/*
 * each card is stored as a single byte of data
 * bits 0-3: card number (1=Ace, 2=2, ... 11=jack. 12=queen, 13=king)
 * bits 4-7: suit number (0=heart, 1=diamond, 2=club, 3=spade)
 * note: a valid card can not be all zeroes
 */

/*
 * three strategies that can be played by the computer
 * 0: random
 * 1: human input
 * 2: sequential (steps through each card in your hand)
 * 3: prioritize (ask groupings of 3 first, then individual cards, then anything else)
 * 4: custom strategy
 */


/* global variables */
int delay = 2;                    /* time delay to slow down simulation */

/* card deck / player info */
struct common deck;
struct fish info[2];

testGame(void);
void User_Intr(void);

int main(int argc, char *argv[])
{
    char text[80];

    srand( time(NULL) );

    if (argc >= 3)
    {
        GoFish("Player-1", atoi(argv[1]), "Player-2", atoi(argv[2]));
        exit(0);
    }

    fprintf(stderr,"Do you want to run the automated test (Y/N)? ");
    gets(text);
    if (text[0] == 'Y' || text[0] == 'y')
       testGame();

    GoFish("", -1, "", -1);

    return(0);
}


/* GoFish
 *   run the go-fish game
 *   input parameters are:
 *     players names and strategy numbers (0-3)
 *   returns which player has won (0/1)
 */
int GoFish(char *name1, int game1, char *name2, int game2)
{
    int card, total;

    Init();

    if (game1 == -1)
    {
        User_Intr();
    }
    else
    {
        /* save the player info */
        strcpy(info[0].name,name1);
        info[0].strategy = game1;

        strcpy(info[1].name,name2);
        info[1].strategy = game2;
    }

    /* begin the game */
    fprintf(stderr,"New Game:  %s (%d)  vs.  %s (%d)\n\n", info[0].name,info[0].strategy, info[1].name,info[1].strategy);
    ShowAll();

    while (1)
    {
        Turn(0);
        ShowAll();
        if (IsGameOver() != 0)
           break;

        Turn(1);
        ShowAll();
        if (IsGameOver() != 0)
           break;
    }

    /* count up the number of groups for player-0 */
    for (total=0, card=MINNUMB; card<=MAXNUMB; card++)
    {
        if (info[0].group[card] != 0)
            total++;
    }

    /* if 7 or more groups, then player-0 has won */
    if (total >= 7)
        return(0);
    return(1);
}
