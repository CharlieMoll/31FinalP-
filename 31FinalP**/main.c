//
//  main.c
//  31FinalP**
//
//  Created by Charles Moll on 4/23/21.
//

#include "main.h"

int main(void){

    printf("hello World");
    
    // ask the user should load from file ? or just shuffle a deck ?
	printf("Do you want to load the cards from the file ? (y/n)\n");
	scanf("%c", userResponse);
	if (userResponse == 'y')
	{
		ReadInCards(&stockPile);
	}
	else
	{
		CreateDeck(&stockPile);
		ShuffleCards(&stockPile);
		ShuffleCards(&stockPile);
	}
	
	printf("There are %d cards in the stockPile - beginning of the game.\n", CountCards(HN));

	// deal first 3 cards from the stockpile to player p1 
	for (int i = 0; i < 3; i++)
	{
		tmp = RemoveNthCard(&stockPile, 1);
		AddNthCard(&(player1->playerCards), tmp, 1);
	}
	printf("There are %d cards in the stockPile - after dealing to first player.\n", CountCards(HN));

	// deal first 3 cards from the stockpile to player p2 
	for (int i = 0; i < 3; i++)
	{
		tmp = RemoveNthCard(&stockPile, 1);
		AddNthCard(&(player2->playerCards), tmp, 1);
	}
	printf("There are %d cards in the stockPile - after dealing to second player.\n", CountCards(HN));

	// initialize the discard pile

	tmp = RemoveNthCard(&stockPile, 1);
	AddNthCard(&discardPile, tmp, 1);

	// betting round:
	
	PlayGame(&player1, &player2, potOfMoney);
    
    return 0;
}
