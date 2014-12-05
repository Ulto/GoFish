#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "gofish.h"
#include "extern.h"

void SortNums(int list[MAXNUMB+1][2], int max);

#define MAX_CARD_COUNT 1

/* Strategy-4
 * This strategy tracks the cards the opponent asks for. If a card is given to the opponent the
 * card will longer be tracked and the priority of the card will be set to zero. An array of card
 * values determines the prority each card could be asked for. If a card in the opponents hand can't
 * be asked for, go to strategy 2.
 */
int Strategy6(int player)
{
    int count = 0, offset = 0;
    int cardnumber = 0;                                             //cardnumber to call
    static int otherhand[2][MAXNUMB+1] = {0};                       //card tracker array
    int card_selection[MAXNUMB+1][2];                               //card sorting array
    int otherplayer = 0;


    otherplayer = 1 - player;

    //other player's card request
    otherhand[ otherplayer ] [ info [ otherplayer ] .lastcard ] += 1;
    //clears priority once a card is asked for
    otherhand[ otherplayer ] [ info [ player ] .lastcard ] = 0;
    //Creates a priority array
    while (count < MAXNUMB+1)
    {
        card_selection[ count ][ 0 ] = count;                               //card value
        card_selection[ count ][ 1 ] = otherhand[ otherplayer ] [ count ];  //number of times the card was asked
        count ++;
    }

    //Sorts the priority array (highest priority on top [][0])
    SortNums(card_selection, MAXNUMB + 1);

    //determines if strategy can be used
    while((card_selection [offset][1] >= MAX_CARD_COUNT) && (offset < MAXNUMB+1))
    {
        cardnumber = TotalNumberOfCards(player,card_selection [offset] [0]);//card number in hand?
        //ask card if you have the card and it wasn't called last
        if ((cardnumber > 0) && (info[player].lastcard != card_selection [offset] [0]))
            return(card_selection[offset][0]);                              //return card value
        else
            offset ++;                                                      //increment offset
    }
    return(Strategy2(player));                                              //Run stategy 2

}
