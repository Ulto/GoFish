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
#define         NUM_STRATEGIES      4
#define         USR_STRATEGY        1

void testGame(void)
{
    // .. put automated test code here ...

    exit(0);
}
