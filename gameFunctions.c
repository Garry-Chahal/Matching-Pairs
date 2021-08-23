// Description: Implement the core functionalities to make the game work.

#include "gameFunctions.h"

// A function that adds the card to the player's winning pile by calling
// the appropriate function from card_LList and update the cards won.
void addCardToPlayer(Player *thePlayer, Card *theCard)
{
  // Insert the card to the front of the linked list
  insertFrontCard_LList(&thePlayer->winPile, theCard);
  thePlayer->cardsWon++;

  // Mark the card as taken by setting its value to 0
  theCard->value = 0;
}

// Function determines the card's index based on column and row
int card_index(char col, char row)
{
  // Matrix index can be determined using x_coor + y_coor * matrix_width
  // Subtract 48 to convert char number to int number,
  // with the width being 13 cards long
  int index = ((int)col - 97) + ((int)row - 48) * (NUM_OF_CARDS_IN_DECK / 4);
  return index;
}

// A function that checks if the user choice is valid:
// if any of the choices are invalid, report that and return false.
bool checkPlayerInput(Deck *theDeck, Player *thePlayer, char row, char col)
{
  // If the row isn't between '0' & '3', and the col isn't between 'a' & 'm'
  if (!(row >= 48 && row <= 51 && col >= 97 && col <= 109))
  {
    puts("ERROR: The card you picked has invalid index(es).");
    return false;
  }

  // If the card value has already been marked as taken (0)
  if (theDeck->cards[card_index(col, row)].value == 0)
  {
    puts("ERROR: The card you picked is already taken.");
    return false;
  }
  return true;
}

// A function that checks if there is a match:
// if the two choices are the same, report it and return false.
// if there is a match, return true; otherwise, return false.
bool checkForMatch(Deck *theDeck, Player *thePlayer,
                   char r1, char c1, char r2, char c2)
{
  int card_index_1 = card_index(c1, r1);
  int card_index_2 = card_index(c2, r2);

  // The two card choices are the same
  if (card_index_1 == card_index_2)
  {
    puts("ERROR: Both cards are the same");
    return false;
  }
  // Else if the value of the two cards are equal, return true
  else if (theDeck->cards[card_index_1].value ==
           theDeck->cards[card_index_2].value)
  {
    return true;
  }
  return false;
}

// A function that checks if the game has a winner
bool checkForWinner(const Deck *theDeck)
{
  // Check whether all cards in the deck are taken (values set to 0)
  for (int i = 0; i < NUM_OF_CARDS_IN_DECK; i++)
  {
    if (theDeck->cards[i].value != 0)
    {
      return false;
    }
  }

  // Return true when there is a winner
  return true;
}