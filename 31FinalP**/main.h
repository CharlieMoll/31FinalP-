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

void AddNthCard(Card **HN, Card *C2A, int N);
void SwapCards(Card **HN,int C1,int C2);
void ShuffleCard(Card **HN);

int CountCards(Card *HN);


#endif /* main_h */
