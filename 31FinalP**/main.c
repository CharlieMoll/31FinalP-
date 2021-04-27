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

	do {

		// Betting part of the round  
		printf("Player 1, how much money do you want to bet?\n");
		scanf("%d", &player1BettingMoney);
		player1->money -= player1BettingMoney;
		potOfMoney += player1BettingMoney;

		printf("Player 2, do you want to meet the bet of player 1 of %d dollars(y/n)?\n", player1BettingMoney);
		scanf("%c", &user2Response);
		if (user2Response == 'n') {
			// player 1 takes the money. game ends.
			player1->money += potOfMoney;
			break;
		}

		// game continues 
		player2->money -= player1BettingMoney;
		potOfMoney += player1BettingMoney;

		printf("Player 2, by how much do you want to raise the bet?");
		scanf("%d", &player2RaiseBet);

		player2->money -= player2RaiseBet;
		potOfMoney += player2RaiseBet;

		if (player2RaiseBet > 0) {
			printf("Player 1, do you want to meet the raise of player 2 of %d dollars (y/n)?", player2RaiseBet);
			scanf("%c", user1Response);
			if (user1Response == 'n') {
				// player 2 takes the money. game ends. 
				break;
			}
			// player1 pays the bet raise
			player1->money -= player2RaiseBet;
			potOfMoney += player2RaiseBet;
		}


		// we are done with betting
		// now card playing


	} while (gameIsPlaying == true);
		
	return(0);
}
    
    
    return 0;
}
