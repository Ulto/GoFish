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
    // .. put user interface code here ...
}


