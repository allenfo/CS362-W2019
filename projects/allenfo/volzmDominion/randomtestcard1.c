#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define DEBUG 0
#define NOISY_Test 1
/*I looked at testDrawCard() function and used that as my base for the test*/
/*This function will test and compare a pre and post gameState*/

int drawCard_fail;
int discardCard_fail;
int hand_fail;
int deck_fail;
int testassert(int a, int b)
{
	if(a==b)
	{
		return 0;//if true
	}
	else
	{
		return 1;// if false
	}
}
void smithyRandTest(int p, struct gameState *post)
{
	int preDraws[3];//cards get drawn 3 times by the function
	int bonus=0;
	struct gameState pre; //setting up a second game so that we can compare
	memcpy (&pre, post, sizeof(struct gameState));
	/*Holds results for that test*/
	int r= cardEffect(smithy,0,0,0, post, 0,&bonus);// should return 0
	/*draws 3 cards and stores then in an array.*/
	for (int i = 0; i < 3; i++)
	{
	  preDraws[i]=drawCard(p, &pre);
	}
	int d= discardCard(0, p, &pre, 0);
	/*Comparing the results*/
	/*Using the testassert function to return true or false*/
	for(int j=0;j<3;j++)
	{
		drawCard_fail=drawCard_fail+ testassert(preDraws[j],0);
	}
	discardCard_fail=discardCard_fail+testassert(d,0);
	deck_fail=deck_fail + testassert(pre.deckCount[p],post->deckCount[p]);
	hand_fail=hand_fail + testassert(pre.handCount[p],post->handCount[p]);
}

int main ()
{
	srand(time(NULL));// keeps the values different everytime
	int testResults=0;
	struct gameState G;
	int deckCount, discardCount, handCount, player;
	printf("Random testing Smithy card.\n");
	int k;
	for(k=0;k<500;k++)
	{
		/*Taken from testDrawCard() to help set up*/
		for(int i=0;i< sizeof(struct gameState);i++)
		{
			((char*)&G)[i]=floor(Random() *256);
		}
		G.numPlayers=(rand() %3)+2;	//between 2 and 4 players
		G.numBuys=1;
		player =(rand() %G.numPlayers);
		deckCount=floor(Random() *MAX_DECK);
		handCount=floor(Random() *MAX_HAND);
		discardCount=floor(Random() *MAX_DECK);
		G.whoseTurn=player;
		G.playedCardCount = floor(Random() * (MAX_DECK - 1));
		for(int j=0;j<G.numPlayers;j++)
		{
			G.deckCount[j]=deckCount;
			G.handCount[j]=handCount;
			G.discardCount[j]=discardCount;
		}
		smithyRandTest(player, &G);
	}
	/*Adds up the fails*/
	testResults= drawCard_fail + discardCard_fail + hand_fail+  deck_fail;
	if(testResults==0)
	{
		printf("ALL TESTS PASS\n");
	}
	else
	{
		printf("SOME TESTS FAILED.\n");
		printf("drawCard() failed %d times.\ndiscardCard() failed %d times\nPlayer's hand count didn't match up %d times.\nPlayer's deck count didn't match up %d times.\n",drawCard_fail, discardCard_fail, hand_fail, deck_fail);
	}
	return 0;
}
