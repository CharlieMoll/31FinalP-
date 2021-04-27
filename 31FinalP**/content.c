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
