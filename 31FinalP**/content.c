//
//  content.c
//  31FinalP**
//
//  Created by Charles Moll on 4/23/21.
//
/*
 Legend:
 Code is from McBride Lecture = #M
 Code is from Lazos Lecture   = #L
 Code is from Notes           = #N
 */

typedef struct Card_s{
    char suit[9];
    int value;
    struct Card_s *pt;
}Card;

int CountCards(Card *HN) { //#M
  int cnt = 0;
  while (1) {
    if (HN == NULL)
      break;
    cnt = cnt + 1;
    HN = HN->pt;
  }
  return(cnt);
}

Card * ReturnNthCardAddress(Card *HN, int N) { //#M
  int i;
  for (i = 1; i < N; i++)
    HN = HN->pt;
  return(HN);
}

void AddNthCard(Card **HN, Card *C2A, int N) { //#M
  Card *tmp;
  if (N > 1) {
    tmp = ReturnNthCardAddress(*HN, N - 1);
    C2A->pt = tmp->pt;
    tmp->pt = C2A;
  }
  else {
    C2A->pt = *HN;
    *HN = C2A;
  }
  return;
}


Card *RemoveNthCard(Card **HN, int N) { //#M
  Card *tmp, *t2;

  if (N > 1) {
    tmp = ReturnNthCardAddress(*HN, N - 1);
    t2 = tmp->pt;
    tmp->pt = t2->pt;
  }
  else {
    t2 = *HN;
    *HN = t2->pt;
  }
  t2->pt = NULL;

  return(t2);
}


void SwapCards(Card **HN,int C1,int C2){ //#M
    
    Card *tmp1,*tmp2;
    int N1, N2;
    N1 = C1 > C2 ? C1 : C2; //N1 is max
    N2 = C1 + C2 - N1;      //N2 is max
    
    tmp1 = RemoveNthCard(HN,N1);
    tmp2 = RemoveNthCard(HN,N2);
    
    AddNthCard(HN,tmp1,N2);
    AddNthCard(HN,tmp2,N1);

    return;
}


void ShuffleCard(Card **HN){      //#M
    int i,j, L = CountCards(*HN);
    for(i = 0; i<= L; i++){
        do{
            j = rand() + 1;
        }while (i == j);
        SwapCards(HN, i, j);
    }
}

void CreateDeck(card** HN) {
	card* tmp;
	char* suits[4] = { "diamonds", "spades", "hearts", "clubs" };
	char* ranks[13]{ "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king", "ace" };
	int pointValues[13]{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 10 };

	*HN = (card*)calloc(sizeof(card), 1);
	tmp = *HN
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 13; ++j) {
			// copy suit into tmp->suit
			strcpy(tmp->suit, suits[i]);
			strcpy(tmp->rank, ranks[j]);
			tmp->value = pointsValues[j];
			if (((i + 1) * (j + 1)) != 52) {
				tmp->pt = (card*)calloc(sizeof(card), 1);
				tmp = tmp->pt;
			}
		}
	}
}

// Code is from McBride lecture
void my_fgets_str(char* userchar, int max_chars, FILE* fptr) {
	do {
		fgets(userchar, max_chars, fptr);
	} while ((userchar[0] == ' ') || (userchar[0] == '\n'));
	while (userchar[strlen(userchar) - 1] == '\n')
		userchar[strlen(userchar) - 1] = '\0';
	return;
}

//Code is from McBride lecture
void ReadInCards(card** HN) {
	card* tmp;
	char Line[1000];
	FILE* filePtr;
	int i, j, cnt = 0;

	filePtr = fopen("cards.txt", "r");
	assert(filePtr != NULL);
	while (!feof(filePtr)) {
		fgets(Line, 1000, filePtr);
		cnt++;
	}
	rewind(filePtr);

	*HN = (card*)calloc(sizeof(card), 1);
	tmp = *HN;
	for (i = 1; i <= cnt; i++) {

		fscanf(filePtr, "%d", &tmp->value); // read the value : points in the game
		my_fgets_str(tmp->suit, 9, filePtr); // read the suit
		my_fgets_str(tmp->rank, 9, filePtr); // read the rank

		if (i < cnt)
			tmp->pt = (card*)calloc(sizeof(card), 1);
		tmp = tmp->pt;
	}
	fclose(ptr);
}

void DealCards(card** HN, player *player1, player *player2, card *stockPile) {
	card* tmp;

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

}

void PlayGame(player *player1, player *player2, int potOfMoney, card *stockPile, card* discardPile) {
	char userResponseChar;
	int userResponseInt;
	char user1ResponseBet;
	int player1BettingMoney;
	int player2RaiseBet;
	bool gameIsPlaying = true;
	int player1Points
	int player2Points
	char user1ResponseGame;
	char user2ResponseGame;
	int user1ResponseGame2;
	int user2ResponseGame2;
	char user1ResponseGame3;
	bool gameEndingNextPlayer;
	card* tmp;

	// betting round:

	do {

		// Betting part of the round  
		printf("Player 1, how much money do you want to bet?\n");
		scanf("%d", &player1BettingMoney);
		player1->money -= player1BettingMoney;
		potOfMoney += player1BettingMoney;

		printf("Player 2, do you want to meet the bet of player 1 of %d dollars(y/n)?\n", player1BettingMoney);
		scanf("%c", &user2ResponseBet);
		if (user2ResponseBet == 'n') {
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
			scanf("%c", &user1ResponseBet);
			if (user1ResponseBet == 'n') {
				// player 2 takes the money. game ends. 
				break;
			}
			// player1 pays the bet raise
			player1->money -= player2RaiseBet;
			potOfMoney += player2RaiseBet;
		}

		// we are done with betting
		// now card playing

		printf("Player 1, would you like to pick a card from the discard pile (enter 'P') or the deck/stock pile (enter 'D')?\n");
		scanf("%c", user1ResponseGame);
		if (user1ResponseGame == 'P' || user1ResponseGame == 'p') {
			tmp = RemoveNthCard(&discardPile, 1);
			AddNthCard(&(player1->playerCards), tmp, 1);
		}
		else if (user1ResponseGame == 'D' || user1ResponseGame == 'd') {
			tmp = RemoveNthCard(&stockPile, 1);
			AddNthCard(&(player1->playerCards), tmp, 1);
		}

		// need to ask player 1 which card they would like to put down in the discard pile

		printf("Player 1, which card would you like to put in the discard pile? (card 1, 2, 3, or 4)");
		scanf("%d", &user1ResponseGame2);

		if (user1ResponseGame2 > 4 || user1ResponseGame2 < 1) {
			user1ResponseGame2 = 1;
		}

		tmp = RemoveNthCard(&(player1->playerCards), user1ResponseGame2);
		AddNthCard(&discardPile, tmp, 1);

		// check if player 2 wanted to end the game; if yes, then end the game
		if (gameEndingNextPlayer == true)
		{
			gameIsPlaying = false;
			break;
		}

		printf("Player 1, do you have 31 points in your hand (y or n)?\n");
		scanf("%c", &user1ResponseGame3);

		if (user1ResponseGame3 == 'y') {
			gameIsPlaying = false;
			break;
		}
		else if (user1ResponseGame3 == 'n') {
			printf("Player 1, do you want to end the game (y or n)?");
			scanf("%c", &user1ResponseGame3);
			if (user1ResponseGame3 == 'y') {
				gameEndingNextPlayer = true; 
			}
		}

		printf("Player 2, would you like to pick a card from the discard pile (enter 'P') or the deck/stock pile (enter 'D')?\n");
		scanf("%c", user2ResponseGame);
		if (user2ResponseGame == 'P' || user2ResponseGame == 'p') {
			tmp = RemoveNthCard(&discardPile, 1);
			AddNthCard(&(player2->playerCards), tmp, 1);
		}
		else if (user2ResponseGame == 'D' || user2ResponseGame == 'd') {
			tmp = RemoveNthCard(&stockPile, 1);
			AddNthCard(&(player2->playerCards), tmp, 1);
		}

		printf("Player 2, which card would you like to put in the discard pile? (card 1, 2, 3, or 4)");
		scanf("%d", user2ResponseGame2);

		if (user2ResponseGame2 > 4 || user2ResponseGame2 < 1) {
			user2ResponseGame2 = 1;
		}

		tmp = RemoveNthCard(&(player2->playerCards), user2ResponseGame2);
		AddNthCard(&discardPile, tmp, 1);

		// check if player1 wanted to end the game; if yes, then end the game
		if (gameEndingNextPlayer == true)
		{
			gameIsPlaying = false;
			break;
		}

		printf("Player 2, do you have 31 points in your hand (y or n)?\n");
		scanf("%c", &user1ResponseGame3);

		if (user1ResponseGame3 == 'y') {
			gameIsPlaying = false;
			break;
		}
		else if (user1ResponseGame3 == 'n') {
			printf("Player 2, do you want to end the game (y or n)?");
			scanf("%c", &user1ResponseGame3);
			if (user1ResponseGame3 == 'y') {
				gameEndingNextPlayer = true;
			}
		}

	} while (gameIsPlaying == true);
}

void DisplayHand(player* playerDisplay) {
	card* tmp;
	int cardCounter = 1;

	tmp = playerDisplay->playerCards;
	while (tmp != NULL) {
		printf("The card #%d: ", cardCounter);
		DisplayCard(tmp);
		cardCounter++;
	}
}

void DisplayCard(card* cardDisplay)
{
	printf("Suit is: %s, and the face value is %s\n", cardDisplay->suit, cardDisplay->rank);
}

// displays everything: 
// display the question for the player that has the turn
// for each player display money available
// for the player that has the turn, display cards
// display the pot money amount
// display the top card of the discard pile

void DisplayBoard(player* player1, player* player2, int potOfMoney, card* discardPile, char* question, int playerInTurn) {
	
	// clear the screen
	printf("\033c");

	printf("=============================\n\n");

	printf("%s\n\n", question);
	
	if (playerInTurn == 1)
	{
		printf("Player 1's money: %d \n", player1->money);
		printf("Player 1's cards: \n");
		DisplayHand(player1);
		printf("\n");

		printf("Player 2's money: %d \n", player2->money);
		printf("\nPlayer 2's cards: Not Visible.\n");
	}

	if (playerInTurn == 2)
	{
		printf("Player 1's money: %d \n", player1->money);
		printf("\nPlayer 1's cards: Not Visible.\n\n");

		printf("Player 2's money: %d \n", player2->money);
		printf("Player 2's cards: \n");
		DisplayHand(player2);
		printf("\n");
	}

	printf("Pot size is %d dollars\n", potOfMoney);

	printf("Top card on the discard pile is:\n");
	card* topDiscardPile = ReturnNthCardsAddress(discardPile, 1);
	DisplayCard(topDiscardPile);

	printf("=============================\n\n");
}

