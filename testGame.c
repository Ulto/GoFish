/* Christopher Conklin
   12/5/2014
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gofish.h"
#include "extern.h"

// Runs every possible combination of strategies a number of times to
// make sure the game does not crash.

// Step through each strategy (0-4)
// Skip over strategy 1 (all others can be automated)
// Run each one "TRIAL_TIMES" and keep records of win-loses
// Display the results


#define         TRIAL_TIMES         25        // how many times to run each strategy against each other
#define         NUM_STRATEGIES      6
#define         USR_STRATEGY        1

void testGame(void)
{
	/*Create index variable*/
	int index = 0;
	char *name;

	/*Create integer variable for game return*/
	int winner = 0;

	/*Create index variable for number of strategies*/
	int randindex = 0;

	/*Create address variable for two strategies*/
	int strategy1 = 0, strategy2 = 0;

	/*Create array for strategy ID numbers*/
	int strategies[NUM_STRATEGIES] = { 0, 2, 3, 4, 5, 6};

	/*Create array for win, lose,and overall count*/
	int wins[NUM_STRATEGIES];
	int loses[NUM_STRATEGIES];
	int overall[NUM_STRATEGIES];

	/*Reset arrays*/
	memset(wins, 0, NUM_STRATEGIES);
	memset(loses, 0, NUM_STRATEGIES);
	memset(overall, 0, NUM_STRATEGIES);

	/*For twenty five random decks*/
	for (randindex = 0; randindex < TRIAL_TIMES; randindex++)
	{
		/*Every strategy will get tested against -> */
		for (strategy1 = 0; strategy1 < NUM_STRATEGIES; strategy1++)
		{
			/* -> strategies left to be tested*/
			for (strategy2 = strategy1; strategy2 < NUM_STRATEGIES; strategy2++)
			{


				/*Test strategies against each other*/
				winner = GoFish("", strategies[strategy1], "", strategies[strategy2]);
			
				/*If returned winner is strategy1*/
				if (winner == strategy1)
				{
					/*Change wins and losses*/
					wins[strategy1]++;
					loses[strategy2]++;

					/*Change overall scores*/
					overall[strategy1]++;
					overall[strategy2]--;
				}
				else
				{
					/*Change wins and losses*/
					wins[strategy2]++;
					loses[strategy1]++;

					/*Change overall scores*/
					overall[strategy2]++;
					overall[strategy1]--;
				}
			}

		}
	}
	/*Print Results*/
	for (index = 0; index < NUM_STRATEGIES; index++)
	{
		/*Switch names, look at index*/
		switch (index)
		{
		case 0:	/*First Basic Strategy*/
			name = "Basic Example "; break;
		case 1: /*Zach's strategy*/
			name = "Zack Cross    "; break;
		case 2: /*Professor Strom simple*/
			name = "Prof. Strom   "; break;
		case 3: /*Dom's strategy*/
			name = "Dom Risaliti  "; break;
		case 4: /*Professor Strom Advanced*/
			name = "Expert Strom  "; break;
		case 5: /*Expert student */
			name = "Expert Student"; break;
		case 6: /*Additional Methods */
			name = "              "; break;
		}
		/*Print strategy results*/
		printf("%s:\tWins: %d\tLoses: %d\tOverall: %d\n",name, wins[index], loses[index], overall[index]);
	}

	/*Wait for character before exit*/
	getch();
    exit(0);
}


