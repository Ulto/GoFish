#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "gofish.h"
#include "extern.h"


/* Strategy-4
 * this technique is to draw as much as possible, increasing the chance
 * that you will get a card you need. So it will pick a random card
 * see if it only has one card, if it does ask for that card. if it picks
 * every card option and none only have 1 card then a random card is picked
 * and is asked for.
 */
int Strategy4(int player)
{
    int card;
	int index;
	int total;
	int flag = 0;
	int check[13] = { 0 };

	while (flag != 1)
	{
		do
		{
			//picking a random card
			card = (rand() % MAXNUMB) + MINNUMB;
			//making sure it hasn't been looked for before
		} while (check[card-1] != 1);
		
		//seeing if there is only one of the card
		if (TotalNumberOfCards(player, card) == 1)
		{
			flag = 1;
		}
		else
		{
			//adding a flag for a card that didn't work.
			check[card-1] = 1;
		}

		//checking to see if every card has been looked at
		for (index = 0,total = 0; index < 13; index++)
		{
			total += check[index];
		}

		//if every card has been tried
		if (total >= 13)
		{
			//pick a random card
			while (1)
			{
				//picking a random card
				card = (rand() % MAXNUMB) + MINNUMB;
				//making sure there is a card in its hand
				if (TotalNumberOfCards(player, card) != 0)
					break;
			}
			break;
		}
	}

    return(card);
}
