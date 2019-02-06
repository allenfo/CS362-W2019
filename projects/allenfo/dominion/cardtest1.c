#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main ()
{
	int numPlayers =2;
	int seed =1000;
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
 	int currentPlayer = whoseTurn(&G);
	int temphand[MAX_HAND];// moved above the if statement
	int  drawntreasure=0;
	int cardDrawn;
	int z = 0;// this is the counter for the temp hand
	initializeGame(numPlayers, k, seed, &G);
	/*Changes that should happen: Hand +2, discard ++*/
	adventurerTest(drawntreasure, currentPlayer, &G,  cardDrawn, temphand, z);
	printf("expected hand count 7, actual was %d\n",G.handCount[currentPlayer]);
	
}
