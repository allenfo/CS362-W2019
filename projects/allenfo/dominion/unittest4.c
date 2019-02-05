/*Testing if isGameOver() is correct.
 * should return 1 if game is over and 0 if it is not over.
 * Has two parameters if it is over: All providince cards are gone or three supply cardspiles are empty
 * */
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
int testassert(int a, int b)
{
	if(a==b)
	{
		printf("PASS\n");
		return 0;
	}
	else
	{
		printf("FAIL\n");
		return 1;
	}
}
int main()
{
	int seed = 1000;
	struct gameState G;
	int k[10] = {adventurer, gardens, treasure_map, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
	#define NOISY_TEST 1
	initializeGame(2, k, seed, &G);
	int player=0;
	printf("Testing gainCard():\n");
#if (NOISY_TEST ==1)
	printf("adding smithy cards to: hand, deck, and discard\n");
#endif
	printf("cards in each spot before running tests:\n deck = %d, hand = %d, discard = %d\n",G.deckCount[player], G.handCount[player], G.discardCount[player]);
	printf("smithy supply before test = %d\n", G.supplyCount[smithy]);
	for(int i=0;i<3;i++)
	{
		if(i==0)
		{
			printf("adding to discard\n");
			gainCard(smithy, &G, i, player);
			printf("expected 1 actual was %d\n",G.discardCount[player]);
			
		}
		else if(i==1)
		{
			printf("adding to deck\n");
			gainCard(smithy, &G, i, player);
			printf("expected 6 actual was %d\n",G.deckCount[player]);
		}
		else
		{
			printf("adding to hand\n");
			gainCard(smithy, &G, i, player);
			printf("expected 6 actual was %d\n",G.handCount[player]);
		}
	}
	printf("expected smithy count 7 actual was %d\n",G.supplyCount[smithy]);
#if (NOISY_TEST ==1)
	printf("trying to add card not in use\n");
#endif
	printf("council_room supply before test = %d\n", G.supplyCount[council_room]);
	for(int i=0;i<3;i++)
	{
		if(i==0)
		{
			printf("adding to discard\n");
			gainCard(council_room, &G, i, player);
			printf("expected 1 actual was %d\n",G.discardCount[player]);
			
		}
		else if(i==1)
		{
			printf("adding to deck\n");
			gainCard(council_room, &G, i, player);
			printf("expected 6 actual was %d\n",G.deckCount[player]);
		}
		else
		{
			printf("adding to hand\n");
			gainCard(council_room, &G, i, player);
			printf("expected 6 actual was %d\n",G.handCount[player]);
		}
	}

return 0;
}
