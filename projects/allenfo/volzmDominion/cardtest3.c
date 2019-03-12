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
	int test1, test2, test3, test4;
	int seed =1000;
	struct gameState G, testG;
	int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
 	int currentPlayer = whoseTurn(&G);
	int temphand[MAX_HAND];// moved above the if statement
	int  handPos=0;
	int cardDrawn;
	int z = 0;// this is the counter for the temp hand
	initializeGame(numPlayers, k, seed, &G);
	initializeGame(numPlayers, k, seed, &testG);
	/*Changes that should happen: Hand +2, discard ++*/
	printf("Testing council_room\n");
	councilroomFunc(handPos, currentPlayer, &testG);
	printf("expected hand count %d, actual was %d\ncouncil_room is not considered part of the hand once played from position 0\n",G.handCount[currentPlayer]+3, testG.handCount[currentPlayer]);
	test1=testassert(G.handCount[currentPlayer]+3, testG.handCount[currentPlayer]);
	printf("Expected total player cards = %d, actual was %d\n",G.discardCount[currentPlayer]+G.deckCount[currentPlayer]+G.handCount[currentPlayer],testG.discardCount[currentPlayer]+testG.deckCount[currentPlayer]+testG.handCount[currentPlayer]);	
	test2=testassert(G.discardCount[currentPlayer]+G.deckCount[currentPlayer]+G.handCount[currentPlayer],testG.discardCount[currentPlayer]+testG.deckCount[currentPlayer]+testG.handCount[currentPlayer]);
	printf("Expected numBuys=%d, Actual =%d\n",G.numBuys+1, testG.numBuys);
	test3=testassert(G.numBuys+1, testG.numBuys);
	printf("Other players expected hand =%d, Actual =%d\n",G.handCount[currentPlayer+1]+1,testG.handCount[currentPlayer+1]);
	test4=testassert(G.handCount[currentPlayer+1]+1, testG.handCount[currentPlayer+1]);
	if(test1==0 &&test2==0&&test3==0&&test4==0)
	{
		printf("ALL TESTS PASSED\n");
	}
	else
	{
		printf("ONE OR MORE TESTS HAVE FAILED\n");
	}
}

