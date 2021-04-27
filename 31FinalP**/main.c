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
	
    
    
    return 0;
}
