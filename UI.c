#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gofish.h"
#include "extern.h"

#define         NUM_STRATEGIES      4
#define         USR_STRATEGY        1

/*
 * User interface:
 *
 * Ask for player1 name, and strategy
 *    copy the name into the field:  info[0].name,name
 *    set the strategy number into:  info[0].strategy
 * Ask for player2 name, and strategy
 *    copy the name into the field:  info[1].name,name
 *    set the strategy number into:  info[1].strategy
 *
 * verify that names and strategies are acceptable
 *
 *    strategy #1 is the human interface
 *    strategy #0 is a random card selection
 *    strategy #2-4 are ones that are to be developed in the class
 */

void User_Intr(void)
{
	int selectStrat;

	printf("Welcome!\n");

	/* Make sure the user puts in a name less than 41 chars */
	do
	{
		printf("Please enter a name for Player 1 (Less than 40 characters): ");

	}while (fgets(info[0].name, 40, stdin) == NULL);

	/* Now let user select strategy. This will repeat until a valid strategy is chosen */
	do{
		printf("Please select the strategy for Player 1 from 0 - 4: ");
		selectStrat = getch();
		if(isdigit(selectStrat))
			selectStrat -= '0';

	} while (selectStrat < 0 || selectStrat > 4);
	
	info[0].strategy = selectStrat;

	/* Make sure the user puts in a name less than 41 chars */
	do{
		printf("\nPlease enter a name for Player 2 (Less than 40 characters): ");
	}while (fgets(info[1].name, 40, stdin) == NULL);

	/* Now let user select strategy. This will repeat until a valid strategy is chosen */
	do{
		printf("Please select the strategy for Player 2 from 0 - 4: ");
		selectStrat = getch();
		if(isdigit(selectStrat))
			selectStrat -= '0';

	} while (selectStrat < 0 || selectStrat > 4);

	info[1].strategy = selectStrat;

}


