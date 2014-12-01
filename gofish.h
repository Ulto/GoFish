#define DELAY     delay              /* time delay variable */

#define MAXSUIT   4                  /* number of suits (Heart,Diamond,Club,Spade) */
#define MAXNUMB  13                  /* number of card numbers (A,2,...,10,J,Q,K) */
#define MINNUMB   1                  /* cards are numbered starting at 1 (ace) */

#define HEART     0
#define DIAMOND   1
#define CLUB      2
#define SPADE     3

#define MAXCARD  (MAXNUMB*MAXSUIT)

struct common {
   int remain;                       /* number of cards remaining in the deck */
   int cards[MAXCARD];               /* draw pile (each card is saved as 1 byte) */
                                     /* where the byte = (suit << 4) | (card number) */
};

struct fish {
   char name[40];                    /* name of the player */
   int strategy;                     /* strategy to be used */
   int lastpick;                     /* last card (number) picked up from the deck */
   int lastcard;                     /* last card (number) asked for */
   int group[MAXNUMB+1];             /* flags to show that a group of 4 has been made */
                                     /* organized by card number (skip over 0)  */
                                     /* note: cards start at number 1 (ace) */
                                     /* and a 1 indicates that we have a group of four */
   int hand[MAXNUMB+1][MAXSUIT];     /* cards that are held in the hand */
                                     /* organized by card number and suit */
                                     /* initialized to 0 */
};


/* main.c */
int GoFish(char *name1, int game1, char *name2, int game2);

/* gofish.c */
void Init(void);
void Shuffle(void);
void Turn(int player);
int CardToAsk(int player);

/* subs.c */
int TransferCard(int dst, int src,int card);
void CheckForGroup(int player, int card);
void DrawNextCard(int player);
int IsGameOver(void);
int TotalNumberOfCards(int player, int card);
int TotalCardsInHand(int player);

/* display.c */
void ShowAll(void);
void ShowHand(int player);
void ShowGroups(int player);
void ShowDeck(void);
char *CardNumb(int card);

/* strategy.c */
int Strategy0(int player);
int Strategy1(int player);
int Strategy2(int player);
int Strategy3(int player);
int Strategy4(int player);
int Strategy5(int player);
