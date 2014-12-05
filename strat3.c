/*
 * This program contains a strategy module for a
 * Go Fish program which prioritizes the greatest
 * grouping of cards as the next card to be asked
 */
#include "gofish.h"
#include "extern.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Strategy-3
*    select a card based on a prioritization scheme
*    first check for groups of 3 cards
*    then check for single cards
*    and then any thing else (groups of 2)
*/
int Strategy3(int player)
{
	int card = 0;
	int index;

	//check all cards until largest group is found
	while (card == 0)
	{
		//check all cards until group of 3 is found
		for (index = 1; index <= MAXNUMB; index++)
		{

			//prevent asking for the same card
			if (index == info[player].lastcard)
				continue;

			//break when group of 3
			if (TotalNumberOfCards(player, index) == 3)
			{
				card = index;
				break;
			}
		}

		//end loop if card is found
		if (card != 0)
			break;

		//check all cards until group of 2 is found
		for (index = 1; index <= MAXNUMB; index++)
		{
			//prevent asking for the same card
			if (index == info[player].lastcard)
				continue;

			//break when group of 2
			if (TotalNumberOfCards(player, index) == 1)
			{
				card = index;
				break;
			}
		}

		//end loop if card is found
		if (card != 0)
			break;

		//check all cards with most in group is found
		for (index = 1; index <= MAXNUMB; index++)
		{

			if (index == info[player].lastcard)
				continue;

			//break when group of 3
			if (TotalNumberOfCards(player, index) == 2)
			{
				card = index;
				break;
			}
		}

		//if no card is found pick random card from hand
		if (card == 0)
			card = Strategy0(player);
	}

	return(card);
}

