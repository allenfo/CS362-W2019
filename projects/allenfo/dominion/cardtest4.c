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
#define NOISY_TEST 1
	int numPlayers =2;
	int test1, test2, test3, test4, test6;
	int seed =1000;
	struct gameState G, testG;
	int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
 	int currentPlayer = whoseTurn(&G);
	int temphand[MAX_HAND];// moved above the if statement
	int  handPos=0;
	int cardDrawn;
	int j = 0;// this is the counter for the temp hand
	initializeGame(numPlayers, k, seed, &G);
	initializeGame(numPlayers, k, seed, &testG);
	/*Changes that should happen: Hand +2, discard ++*/
	printf("Testing mine\n");
#if NOISY_TEST ==1
	printf("Testing function with a non treasure card\n");
	test1=mineTest(j,&testG, smithy, gold, silver, currentPlayer,0);
	printf("expected return -1, actual was %d\n",test1);
	testassert(-1,test1);
#endif
#if NOISY_TEST==1
	printf("Testing function with correct trash card(treasure) but not correct gain card\n");
	testG.hand[currentPlayer][0]=gold;
	test2=mineTest(j,&testG, gold, 28, silver, currentPlayer,0);
	printf("expected return -1, actual was %d\n",test2);
	testassert(-1,test2);
#endif
#if NOISY_TEST==1
	printf("Testing function with correct trash card(gold) but not correct difference in cost(bronze)\n");
	testG.hand[currentPlayer][0]=gold;
	test3=mineTest(j,&testG, gold, copper, silver, currentPlayer,0);
	printf("expected return -1, actual was %d\n",test3);
	testassert(-1,test3);
#endif
#if NOISY_TEST==1
	printf("Testing function with correct trash card(copper) with correct diff in cost but not correct type(village)\n");
	testG.hand[currentPlayer][0]=copper;
	test4=mineTest(j,&testG, copper, village, silver, currentPlayer,0);
	printf("expected return -1, actual was %d\n",test4);
	testassert(-1,test4);
#endif
#if NOISY_TEST==1
	printf("Testing function with correct trash card(copper) with correct gain card(silver)\n");
	testG.hand[currentPlayer][0]=copper;
	mineTest(j,&G, copper, village, silver, currentPlayer,0);
	test6=G.handCount[currentPlayer];
	printf("expected 5 cards in hand, actual was %d\n",G.handCount[currentPlayer]);
	testassert(5,test6);
#endif
	if(test1==-1 &&test2==-1&&test3==-1&&test4==-1 &&test6==5)
	{
		printf("ALL TESTS PASSED\n");
	}
	else
	{
		printf("ONE OR MORE TESTS HAVE FAILED\n");
	}
}

