#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
int testassert(int a, int b)
{
	if(a==b)
	{
		printf("PASSED\n");
		return 0;
	}
	else
	{
		printf("FAIL\n");
		return 1;
	}
}
int main ()
{
	int numPlayers =2;
	int test1, test2;
	int seed =1000;
	struct gameState G, testG;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
 	int currentPlayer = whoseTurn(&G);
	int temphand[MAX_HAND];// moved above the if statement
	int  drawntreasure=0;
	int cardDrawn;
	int z = 0;// this is the counter for the temp hand
	initializeGame(numPlayers, k, seed, &G);
	initializeGame(numPlayers, k, seed, &testG);
	/*Changes that should happen: Hand +2, discard ++*/
	printf("Testing the adventurer card\n");
	adventurerFunc(0, currentPlayer, &testG, drawntreasure, temphand, z);
	int gainedcards= 2;
	printf("expected hand count %d, actual was %d\n",G.handCount[currentPlayer]+gainedcards, testG.handCount[currentPlayer]);
	test1=testassert(G.handCount[currentPlayer]+gainedcards, testG.handCount[currentPlayer]);
	printf("Expected total player cards = %d, actual was %d\n",G.discardCount[currentPlayer]+G.deckCount[currentPlayer]+G.handCount[currentPlayer],testG.discardCount[currentPlayer]+testG.deckCount[currentPlayer]+testG.handCount[currentPlayer]);	
	test2=testassert(G.discardCount[currentPlayer]+G.deckCount[currentPlayer]+G.handCount[currentPlayer],testG.discardCount[currentPlayer]+testG.deckCount[currentPlayer]+testG.handCount[currentPlayer]);
	if(test1==test2)
	{
		printf("ALL TESTS PASSED\n");
	}
	else
	{
		printf("ONE OR MORE TESTS HAVE FAILED\n");
	}
}
