#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "gofish.h"
#include "extern.h"

#include <assert.h>


int Strategy5(int player)
{
	/* keep track of the last card the other person asked for */
	static int list[2][MAXNUMB + 1] = { 0 };
	static int count[2] = { MINNUMB, MINNUMB };
	int card, cnt;

	assert(player == 0 || player == 1);

	/* add the last card asked to a table */
	card = info[1 - player].lastcard;
	list[player][card] = 1;

	for (card = MINNUMB; card <= MAXNUMB; card++)
	{
		if (list[player][card] == 0)
			continue;

		cnt = TotalNumberOfCards(player, card);
		if (cnt != 0)
		{
			list[player][card] = 0;
			return(card);
		}
	}

	for (card = MINNUMB; card <= MAXNUMB; card++)
	{
		if (++count[player] > MAXNUMB)
			count[player] = MINNUMB;
		card = count[player];
		if (TotalNumberOfCards(player, card) == 3)
		{
			list[player][card] = 0;
			return(card);
		}
	}

	for (card = MINNUMB; card <= MAXNUMB; card++)
	{
		if (++count[player] > MAXNUMB)
			count[player] = MINNUMB;
		card = count[player];
		if (TotalNumberOfCards(player, card) == 1)
		{
			list[player][card] = 0;
			return(card);
		}
	}

	for (card = MINNUMB; card <= MAXNUMB; card++)
	{
		if (++count[player] > MAXNUMB)
			count[player] = MINNUMB;
		card = count[player];
		if (TotalNumberOfCards(player, card) == 2)
		{
			list[player][card] = 0;
			return(card);
		}
	}

	return(Strategy0(player));
}
