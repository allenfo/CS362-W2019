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
int numBuys_fail;
int drawCard_fail;
int discardCard_fail;
int hand_fail;
int deck_fail;
int otherPlayers_fail;
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
void council_roomRandTest(int p, struct gameState *post)
{
	int playerDraws[post->numPlayers]; //max_players is 4
	int preDraws[4];			//cards get drawn 4 times by the function
	int bonus=0;
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	/*Holds results for that test*/
	int r= cardEffect(council_room,0,0,0, post, 0,&bonus);
	/*draws 4 cards and stores then in an array.*/
	for (int i = 0; i < 4; i++)
	{
	  preDraws[i]=drawCard(p, &pre);
	}
			
      //+1 Buy
        pre.numBuys++;
       //Each other player draws a card
for (int i = 0; i < pre.numPlayers; i++)
	{
	  if ( i != p )
	    {
	     playerDraws[i]=drawCard(i, &pre);
		otherPlayers_fail=otherPlayers_fail + testassert(playerDraws[i],0);
	    }
	}
			
      //put played card in played card pile
     int d= discardCard(0, p, &pre, 0);

/*Comparing the results*/
numBuys_fail=numBuys_fail+testassert(pre.numBuys,post->numBuys);
for(int j=0;j<4;j++)
{
	drawCard_fail=drawCard_fail+ testassert(preDraws[j],0);
}
discardCard_fail=discardCard_fail+testassert(d,0);
deck_fail=deck_fail + testassert(pre.deckCount[p],post->deckCount[p]);
hand_fail=hand_fail + testassert(pre.handCount[p],post->handCount[p]);
}


int main ()
{
	srand(time(NULL));// keeps values random and changing
	int testResults=0;
	struct gameState G;
	int deckCount, discardCount, handCount, player;
	printf("Random testing Council_room card.\n");
	int k;
	for(k=0;k<500;k++)
	{
		/*Set up same as testDrawCard()*/
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
		council_roomRandTest(player, &G);
	}
	/*Adds up the fails*/
	testResults=numBuys_fail + drawCard_fail + discardCard_fail + hand_fail+  deck_fail + otherPlayers_fail;
	if(testResults==0)
	{
		printf("ALL TESTS PASS\n");
	}
	else
	{
		printf("SOME TESTS FAILED.\n");
		printf("numBuys failed %d times.\ndrawCard() failed %d times.\ndiscardCard() failed %d times\nPlayer's hand count didn't match up %d times.\nPlayer's deck count didn't match up %d times.\nOther player's drawCard() failed %d times.\n",numBuys_fail, drawCard_fail, discardCard_fail, hand_fail, deck_fail, otherPlayers_fail);
	}
	return 0;
}
