// Description: Implements functions that manage the entities of the game

#include "gameObjects.h"

// A function that initializes all the fields of a Deck.
// For each suit, the values of the cards are
// ‘A’, ‘2’, ‘3’, …, ‘9’, ,'T', ‘J’, ‘Q’, ‘K’.
void initializeDeck(Deck *theDeck, char *brandName)
{
  // Initalize the brand as the cstring "Bicycle"
  theDeck->brand = brandName;

  // All 12 possible card values for each suit, T represents 10
  char cardvalue[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9',
                      'T', 'J', 'Q', 'K'};

  // Starting from 0, increment till we reach 52 cards
  int card_counter = 0;

  // Initalize the Spades suit with each card value
  // 13 cards in each row
  for (int i = 0; i < 13; i++)
  {
    theDeck->cards[card_counter].suit = Spades;
    theDeck->cards[card_counter].value = cardvalue[i];
    // Increment card_counter to move forward to the next array index
    card_counter++;
  }

  // Initalize the Hearts suit with each card value
  for (int i = 0; i < 13; i++)
  {
    theDeck->cards[card_counter].suit = Hearts;
    theDeck->cards[card_counter].value = cardvalue[i];
    card_counter++;
  }

  // Initalize the Clubs suit with each card value
  for (int i = 0; i < 13; i++)
  {
    theDeck->cards[card_counter].suit = Clubs;
    theDeck->cards[card_counter].value = cardvalue[i];
    card_counter++;
  }

  // Initalize the Diamonds suit with each card value
  for (int i = 0; i < 13; i++)
  {
    theDeck->cards[card_counter].suit = Diamonds;
    theDeck->cards[card_counter].value = cardvalue[i];
    card_counter++;
  }
}

// A function that shuffles the deck
void shuffleDeck(Deck *theDeck)
{
  size_t i;

  // Loop through the cards and swap each card with another at a random index
  for (i = 0; i < NUM_OF_CARDS_IN_DECK - 1; i++)
  {
    // Use rand() instead of srand() to ensure marking consistency.
    size_t j = i + rand() / (RAND_MAX / (NUM_OF_CARDS_IN_DECK - i) + 1);

    // Swapping the two cards
    Card temp = theDeck->cards[j];
    theDeck->cards[j] = theDeck->cards[i];
    theDeck->cards[i] = temp;
  }
}

// Function that prints the suit symbol associated to a card index
void printSymbol(const Deck *theDeck, int index)
{
  // Get the suit name for the current card index
  Suit card_suit = theDeck->cards[index].suit;

  switch (card_suit)
  {
  // Case 0 is Spades
  case 0:
    printf("\u2660 ");
    break;

  // Case 1 is Hearts
  case 1:
    printf("\u2661 ");
    break;

  // Case 2 is Clubs
  case 2:
    printf("\u2663 ");
    break;

  // Case 3 is Diamonds
  case 3:
    printf("\u2662 ");
    break;

  default:
    break;
  }
}

// A function that prints the content of a Deck.
// accepts a second bool parameter to indicate Deck face-up/down
void printDeck(const Deck *theDeck, bool faceUp)
{
  // Print all the horizontal letters above the deck
  printf(" ");
  for (char letter = 'a'; letter <= 'm'; letter++)
  {
    printf("  %c", letter);
  }

  // Keeps track of the current row
  int row_count = 0;

  for (int i = 0; i < NUM_OF_CARDS_IN_DECK; i++)
  {
    // Print a new line and row number for each row
    if (i == 0 || i == 13 || i == 26 || i == 39)
    {
      printf("\n");
      printf("%d ", row_count);
      row_count++;
    }
    // Print the deck face up
    if (faceUp == true)
    {
      // Print the card value
      printf("%c", theDeck->cards[i].value);

      // Get the suit symbol for this card
      printSymbol(theDeck, i);
    }
    // Print the deck face down
    if (faceUp == false)
    {
      // If the card is still available (value not assigned 0)
      if (theDeck->cards[i].value != 0)
      {
        // Print a ? and empty box to symbolize the card
        printf("%c\u218C ", '?');
      }
      else
      {
        // Card is not available - already won.
        // Print a blank space for that position
        printf("   ");
      }
    }
  }
  printf("\n");
}

// A function that initializes all the fields of a Player.
void initializePlayer(Player *thePlayer, char *theName)
{
  // Initialize the fields of thePlayer to the initial default
  thePlayer->name = theName;
  thePlayer->cardsWon = 0;

  // Set the head & tail for the player's linked list
  thePlayer->winPile.head = NULL;
  thePlayer->winPile.tail = NULL;
}

// A function clears the winning pile of the player by calling the necessary
// function on a Card_LList.
void clearPlayer(Player *thePlayer)
{
  clearCard_LList(&thePlayer->winPile);
  thePlayer->cardsWon = 0;
}