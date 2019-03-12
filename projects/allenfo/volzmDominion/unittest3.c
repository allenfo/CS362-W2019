/*Testing if drawCard() is correct.
 *  * The game adds a card to the players hand from their deck
 *   * */
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
	int player =0;//player 1
	initializeGame(2, k, seed, &G);
	printf("Testing drawCard():\n");
	printf("deck count is currently  =%d\n",G.deckCount[player]);
	printf("hand count is currently =%d\n",G.handCount[player]);
	printf("discard count is currently =%d\n",G.discardCount[player]);
#if (NOISY_TEST ==1)
	printf("Setting deckCount=0 and discard =5\n");
#endif
	G.deckCount[player]=0;
	G.discardCount[player]=5;
	int i = drawCard(player, &G);
	printf("expected deck count = 4, actual deck  count is now  =%d\n",G.deckCount[player]);
	printf("expected hand count =6, actual hand count is now =%d\n",G.handCount[player]);
	printf("expected discard count =0 actual discard count is now =%d\n",G.discardCount[player]);
	printf("function should return 0, it returned %d\n",i);
	testassert(G.deckCount[player],4);
	testassert(G.handCount[player],6);
	testassert(G.discardCount[player],0);
	testassert(i,0);
#if (NOISY_TEST ==1)
	printf("Setting deckCount=1 and discard =4\n");
#endif
	G.deckCount[player]=1;
	G.discardCount[player]=4;
	G.handCount[player]=5;
	int j = drawCard(player, &G);
	printf("expected deck count = 0, actual deck  count is now  =%d\n",G.deckCount[player]);
	printf("expected hand count =6, actual hand count is now =%d\n",G.handCount[player]);
	printf("expected discard count =4 actual discard count is now =%d\n",G.discardCount[player]);
	printf("function should return -1, it returned %d\n",i);
	testassert(G.deckCount[player],0);
	testassert(G.handCount[player],6);
	testassert(G.discardCount[player],4);
	testassert(i,-1);


}
