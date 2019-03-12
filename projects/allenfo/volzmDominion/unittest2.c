/*Testing if isGameOver() is correct.
 *  * should return 1 if game is over and 0 if it is not over.
 *   * Has two parameters if it is over: All providince cards are gone or three supply cardspiles are empty
 *    * */
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
	printf("Testing isGameOver():\n");
#if (NOISY_TEST ==1)
	printf("Setting Province supplyCount=0\n");
#endif
	G.supplyCount[province]=0;
	int j = isGameOver(&G);
	printf("Expected output =%d, actual output =%d\n",1,j);
	testassert(j,1);
	G.supplyCount[province]=10; //setting it back to test isGameOver() second parameter
#if (NOISY_TEST ==1)
	printf("Setting three supply cards equal to 0.\nOne will be the last eNum card listed\n");
#endif
	G.supplyCount[gardens]=0;
	G.supplyCount[treasure_map]=0;//last card listed on the enum list
	G.supplyCount[mine]=0;
	int i= isGameOver(&G);
	printf("Expected output =%d, actual output =%d\n",1,i);
	testassert(i,1);
	if (i==j)
	{
	printf("ALL TESTS PASSED\n");
	return 0;
	}
	else
	{
	printf("ONE OR MORE TESTS FAILED\n");
	return 0;
	}

}
