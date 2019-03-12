/*testing whoseTurn()*/
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
/*Testing the whoseturn() function*/
int main ()
{
	int numPlayers =2;
	int seed =1000;
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
	printf ("Starting test of the whoseTurn() function.\n");
	printf("There are %d players in this game\n",numPlayers);
/* Setting up the game*/
	printf("This loop will cycle through twice to show that the whose turn function returns the correct person\n");
  	initializeGame(numPlayers, k, seed, &G);
	for(int i =0; i<numPlayers;i++)
	{
		int j= whoseTurn(&G);
		if(j==i)
		{
		printf("It is player %d's turn\n",j);
		endTurn(&G);
		}
	}
	
}

