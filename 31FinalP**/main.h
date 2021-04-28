//
//  main.h
//  31FinalP**
//
//  Created by Charles Moll on 4/23/21.
//

#ifndef main_h
#define main_h

#include <stdio.h> //all libraries here
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "content.c"
// all function prototypes go here
Card * ReturnNthCardAddress(Card *HN, int N);
Card *RemoveNthCard(Card **HN, int N);

void my_fgets_str(char* userchar, int max_chars, FILE* fptr);
void AddNthCard(Card **HN, Card *C2A, int N);
void SwapCards(Card **HN,int C1,int C2);
void ShuffleCard(Card **HN);
void CreateDeck(card** HN);
int CountCards(Card *HN);
void ReadInCards(card** HN);
void PlayGame(player* player1, player* player2, int potOfMoney, card* stockPile, card* discardPile);


#endif /* main_h */
