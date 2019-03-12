#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
int testassert(int a, int b)
{
	if(a==b)
	{
		return 1;//if true
	}
	else
	{
		return 0;// if false
	}
}
int main ()
{
	srand(time(NULL));
	int passedTests=0;
	int failedTests=0;
	/*Players have to be between 2 and 4*/
	int numPlayers =(rand() %2)+2;
	printf("Random testing Adventurer card.\nTest #1: Gaining two cards to players hand.\nTest #2: Making sure total cards do not change.\n");
	int k;
	for(k=0;k<1000;k++)
	{
		int test1, test2;
		struct gameState G;
 		int currentPlayer = 0;
		int deckSize=(rand() %(MAX_DECK -2)+2);
		int handSize=0;
		/*for the function to work there needs to be at least two cards in the  deck*/
		if(deckSize>2)
		{
			handSize=(rand() %(deckSize-2));
		}
		deckSize=deckSize-handSize;
		G.handCount[currentPlayer]=handSize;
		G.deckCount[currentPlayer]=deckSize;
		G.discardCount[currentPlayer]=0;
		for(int i=0;i<deckSize;i++)
		{
			int randCard=(rand()%7)+12;
			G.deck[0][i]=randCard;
		}
		int treasure1=(rand() % deckSize-1);
		int treasure2=(rand() % deckSize-1);
		while(treasure1 == treasure2)
		{
			treasure2=(rand() % deckSize-1);
		}
		G.deck[0][treasure1]=gold;
		G.deck[0][treasure2]=silver;
	
		int temphand[MAX_HAND];// moved above the if statement
		int  drawntreasure=0;
		int cardDrawn;
		int z = 0;// this is the counter for the temp hand
		/*Changes that should happen: Hand +2, discard ++*/
		adventurerFunc(0, currentPlayer, &G, drawntreasure, temphand, z);
		int gainedcards= 2;
		/*Testing if the player gained 2 cards*/
		test1=testassert(handSize+gainedcards, G.handCount[currentPlayer]);
		/*Testing that the player only gained cards from their deck*/
		test2=testassert(deckSize+handSize,G.discardCount[currentPlayer]+G.deckCount[currentPlayer]+G.handCount[currentPlayer]);
		if(test1==1 &&test2==1)
		{
			passedTests++;
		}
		else
		{
			failedTests++;
		}
	}
printf("The adventurer card passed all tests %d times and failed one ore more tests %d times\n",passedTests, failedTests);
}
