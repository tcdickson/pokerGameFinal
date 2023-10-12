
/*  Determine whether the hand contains a pair.

  Determine whether the hand contains two pairs.

  Determine whether the hand contains three of a kind (e.g., three jacks).

  Determine whether the hand contains four of a kind (e.g., four aces).

  Determine whether the hand contains a flush (i.e., all five cards of the same suit).

  Determine whether the hand contains a straight (i.e., five cards of consecutive face values).*/

// Including C Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// define array sizes
#define SUITS 4
#define FACES 13
#define FACECARD 4
#define CARDS 52

// function prototypes
void shuffle(unsigned int wDeck[][FACES]); // shuffling modifies wDeck
void deal(unsigned int wDeck[][FACES], const char *wFace[],
          const char *wSuit[]); // dealing doesn't modify the arrays
bool pair(unsigned int (*hand)[FACES]);
bool twoPair(unsigned int (*hand)[FACES]);
bool threeKind(unsigned int (*hand)[FACES]);
bool fourKind(unsigned int (*hand)[FACES]);
bool flush(unsigned int (*hand)[FACES]);
bool straight(unsigned int (*hand)[FACES]);
bool testLoop(unsigned int (*hand)[FACES]);

int main(void)
{
    // initialize deck array
    unsigned int deck[SUITS][FACES] = {0};

    srand(time(NULL)); // seed random-number generator

    shuffle(deck); // shuffle the deck

    // initialize suit array
    const char *suit[SUITS] =
        {"Hearts", "Diamonds", "Clubs", "Spades"};

    // initialize face array
    const char *face[FACES] =
        {"Ace", "Deuce", "Three", "Four",
         "Five", "Six", "Seven", "Eight",
         "Nine", "Ten", "Jack", "Queen", "King"};
    // initialize facecard array
    const char *faceCard[FACECARD] =
        {"Ace", "Jack", "Queen", "King"};
    // deal the deck
    deal(deck, face, suit);
}

// shuffle cards in deck
void shuffle(unsigned int wDeck[][FACES])
{
    // for each of the cards, choose slot of deck randomly
    for (size_t card = 1; card <= CARDS; ++card)
    {
        // row number
        size_t row;
        // column number
        size_t column;
        // choose new random location until unoccupied slot found
        do
        {
            row = rand() % SUITS;
            column = rand() % FACES;
            // end do...while
        } while (wDeck[row][column] != 0);

        // place card number in chosen slot of deck
        wDeck[row][column] = card;
    }
}

// deal cards in deck
void deal(unsigned int wDeck[][FACES], const char *wFace[],
          const char *wSuit[])
{
    printf("Five-card poker hand:\n");
    // Initialize hand array
    unsigned int hand[FACES] = {0};

    // Deal each of the cards. Poker requires a 5 card hand. Therefore we limit the loop to 5.
    for (size_t card = 1; card <= 5; ++card)
    {
        // Loop through rows of wDeck
        for (size_t row = 0; row < SUITS; ++row)
        {
            // loop through columns of wDeck for current row
            for (size_t column = 0; column < FACES; ++column)
            {
                // if slot contains current card, display card
                if (wDeck[row][column] == card)
                {
                    // print 5 card hand in 2 column format
                    printf("%5s of %-8s%c", wFace[column], wSuit[row],
                           card % 2 == 0 ? '\n' : '\t');
                    // hand is reference by the pointer. Increments the count of face value cards in the hand array. Allows access to all conditional logic below        
                    hand[column]++;
                }
            }
        }
    }
    // Here we initialize hasPairResult to the pair function written below. The pair function contains a pointer that references the hand array initialized at zero. This points to the initialized hand array in the deal function.
    bool hasPairResult = pair(&hand[0]);
    // conditional logic that references the pair function. Printing the result if the array contains one pair, and returning else statement if it doesnt.
    if (hasPairResult)
    {
        printf("\n\nThe hand contains one pair.\n");
    }
    else
    {
        // return false;
        printf("\n\nThe hand does not contain a pair.\n");
    }
    // Here we initialize hasTwoPairResult to the twopair function written below. The twoPair function contains a pointer that references the hand array initialized at zero. This points to the initialized hand array in the deal function.
    bool hasTwoPairResult = twoPair(&hand[0]);
    // conditional logic that references the twoPair function. Printing the result if the array contains two pairs, and printing else statement  if it doesnt.
    if (hasTwoPairResult)
    {
        printf("\nThe hand contains two pairs.\n");
    }
    else
    {
        // return false;
        printf("\nThe hand does not contain 2 pairs.\n");
    }
    // Here we initialize ThreeKindPairResult to the threeKind function written below. The threeKind function contains a pointer that references the hand array initialized at zero. This points to the initialized hand array in the deal function.
    bool hasThreeKindResult = threeKind(&hand[0]);
    // conditional logic that references the threeKind function. Printing the result if the array contains three of a kind, and printing else statement  if it doesnt.
    if (hasThreeKindResult)
    {
        printf("\nThe hand contains three of a kind.\n");
    }
    else
    {
        // return false;

        printf("\nThe hand does not contain three of a kind.\n");
    }
    // Here we initialize hasFourKindResults to the fourKind function written below. The fourKind function contains a pointer that references the hand array initialized at zero. This points to the initialized hand array in the deal function.
    bool hasFourKindResults = fourKind(&hand[0]);
    // conditional logic that references the fourKind function. Printing the result if the array contains four of a kind, and printing else statement if it doesnt.
    if (hasFourKindResults)
    {
        printf("\nThe hand contains four of a kind.\n");
    }
    else
    {
        // return false;
        printf("\nThe hand does not contain four of a kind.\n");
    }
    // Here we initialize hasFlushResults to the flush function written below. The flush function contains a pointer that references the hand array initialized at zero. This points to the initialized hand array in the deal function.
    bool hasFlushResults = flush(&hand[0]);
    // conditional logic that references the flush function. Printing the result if the array contains a flush, and printing else statement if it doesnt.
    if (hasFlushResults)
    {
        printf("\nThe hand contains five of a kind (flush).\n");
    }
    else
    {
        // return false;
        printf("\nThe hand does not contain a flush.\n");
    }
    // Here we initialize hasStraightResults to the straight function written below. The straight function contains a pointer that references the hand array initialized at zero. This points to the initialized hand array in the deal function.
    bool hasStraightResults = straight(&hand[0]);
    if (hasStraightResults)
    {
        printf("\nThe hand contains a straight.\n");
    }
    else
    {
        // return false;
        printf("\nThe hand does not contain a straight.\n");
    }
}
// Here we create the pair funtion. The unsigned int takes an array parameter as a pointer. In code above, we use this function to access the hand array.
bool pair(unsigned int (*hand)[FACES])
{
    // looping through FACES values, if any element in the hand array (which is accessed through the pointer *hand) contains 2 of the same face values, we have found our pair, and return true. If not - false. This function is used in code above.
    for (size_t i = 0; i < FACES; ++i)
    {
        if ((*hand)[i] == 2)
        {
            // Pair found
            return true;
        }
    }
    return false;
}
// Here we create the twoPair funtion. The unsigned int takes an array parameter as a pointer. In code above, we use this function to access the hand array.
bool twoPair(unsigned int (*hand)[FACES])
{
    // Here we use a nested for loop to loop through the FACES values for separate i and j variables. This allows us to write an if statement that returns true if the i and the j variables contain 2. Code above accesses this function to print a message if our hand array contains 2 pairs.
    for (size_t i = 0; i < FACES; ++i)
    {
        for (size_t j = i + 1; j < FACES; ++j)
        {

            if ((*hand)[i] == 2 && (*hand)[j] == 2)
            {
                return true;
            }
        }
    }
    return false;
}
// Here we create the threeKind funtion. The unsigned int takes an array parameter as a pointer. In code above, we use this function to access the hand array.
bool threeKind(unsigned int (*hand)[FACES])
{
    // looping through FACES values, if any element in the hand array (which is accessed through the pointer *hand) contains 3 of the same face values, we have found our three of a kind, and return true. If not - false. This function is used in code above.
    for (size_t i = 0; i < FACES; ++i)
    {
        if ((*hand)[i] == 3)
        {
            return true;
        }
    }
    return false;
}
// Here we create the fourKind funtion. The unsigned int takes an array parameter as a pointer. In code above, we use this function to access the hand array.
bool fourKind(unsigned int (*hand)[FACES])
{
    // looping through FACES values, if any element in the hand array (which is accessed through the pointer *hand) contains 4 of the same face values, we have found our four of a kind, and return true. If not - false. This function is used in code above.
    for (size_t i = 0; i < FACES; ++i)
    {
        if ((*hand)[i] == 4)
        {
            return true;
        }
    }
    return false;
}
// Here we create the flush funtion. The unsigned int takes an array parameter as a pointer. In code above, we use this function to access the hand array.
bool flush(unsigned int (*hand)[FACES])
{
    // looping through FACES values, if any element in the hand array (which is accessed through the pointer *hand) contains 5 of the same face values, we have found our flush, and return true. If not - false. This function is used in code above.
    for (size_t i = 0; i < FACES; ++i)
    {
        if ((*hand)[i] == 5)
        {
            return true;
        }
    }
    return false;
}
// Here we create the straight funtion. The unsigned int takes an array parameter as a pointer. In code above, we use this function to access the hand array.
bool straight(unsigned int (*hand)[FACES])
{
    // looping through FACES values, if any element in the hand array (which is accessed through the pointer *hand) contains 5 FACECARD values, we have found our straight, and return true. If not - false. This function is used in code above.
    for (size_t i = 0; i < FACES; ++i)
    {
        for (size_t i = 0; i < FACECARD; ++i)
        {
            if ((*hand)[i] == 5)
            {
                return true;
            }
        }
    }
    return false;
}
