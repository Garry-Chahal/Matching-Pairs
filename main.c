/*
Description: This is the source code for the game. In implements the main
function that is the driver of the program. In also includes a clear function
that attemps to "push" the face up print up beyond the screen.
*/

#include <stdio.h>

// <stdlib.h> for the use of system and srand and rand
#include <stdlib.h>
#include "gameObjects.h"
#include "gameFunctions.h"

// Each input should have at most 15 characters
#define MAX_CHAR_NUMBER 16

// A helper function that clears the screen, works for both unix and Windows,
// though behaviour might be different.
// https://stackoverflow.com/questions/2347770/
// how-do-you-clear-the-console-screen-in-c
void clear()
{
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
  system("printf '\33[H\33[2J'");
#endif

#if defined(_WIN32) || defined(_WIN64)
  system("cls");
#endif
}

// Function that prints the suit symbol associated to a card index
void printCardSymbol(const Deck *theDeck, int index)
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

int main()
{
  // Set the random seed to 0, it'll generate the same sequence
  // normally it is srand(time(NULL)) so the seed is different in every run
  // using 0 makes it deterministic so it is easier to mark
  srand(0);

  // Variables to store user input
  char userInput1[MAX_CHAR_NUMBER];
  char userInput2[MAX_CHAR_NUMBER];

  // Set up the players
  Player player1, player2;
  initializePlayer(&player1, "Player 1");
  initializePlayer(&player2, "Player 2");

  // This pointer remembers who's turn it is
  Player *currentPlayer = &player1;

  // Set up the deck: initalize & shuffle
  Deck myDeck;
  initializeDeck(&myDeck, "Bicycle");
  shuffleDeck(&myDeck);

  // Print the shuffled deck, face up
  printDeck(&myDeck, true);
  printf("\n");

  // Clear the screen to hide the face up deck
  clear();

  /*
  Implement this part for the game to work.
  It is essentially a do-while loop that repeatedly print the deck,
  ask for user inputs, and do some checking. Ends if someone wins.
  */
  do
  {
    // Step 1: print the shuffled deck, face down
    printDeck(&myDeck, false);

    // Step 2: print who's turn it is by showing the player's name
    printf("\n%s's turn.\n", currentPlayer->name);

    // Step 3.1 get first input from player,
    // keep asking until the input is valid (hint: use a do-while loop)
    // you can assume that the format is correct (a digit<space>a letter)
    do
    {
      // Printing over 2 lines to keep under 80 character limit.
      printf("Print the first card you want to turn (e.g., 0 a) "
             "then press enter: ");
      scanf(" %c %c", &userInput1[0], &userInput1[1]);
    } while (!(checkPlayerInput(&myDeck, currentPlayer,
                                userInput1[0], userInput1[1])));

    // Step 3.2: get second input from player,
    // keep asking until the input is valid (hint: use a do-while loop)
    // you can assume that the format is correct (a digit<space>a letter)
    do
    {
      printf("Print the second card you want to turn (e.g., 1 b) "
             "then press enter: ");
      scanf(" %c %c", &userInput2[0], &userInput2[1]);

    } while (!(checkPlayerInput(&myDeck, currentPlayer,
                                userInput2[0], userInput2[1])));

    // Step 4: print the 2 cards the player picks
    // Matrix index can be determined using x_coor + y_coor * matrix_width
    // Subtract 48 to convert char number to int number,
    // with the width being 13 cards long
    int card_index1 = (userInput1[1] - 97) +
                      (userInput1[0] - 48) * (NUM_OF_CARDS_IN_DECK / 4);
    int card_index2 = (userInput2[1] - 97) +
                      (userInput2[0] - 48) * (NUM_OF_CARDS_IN_DECK / 4);

    // Print both cards based on the index calculated
    printf("\nFirst card picked: %c", myDeck.cards[card_index1].value);
    printCardSymbol(&myDeck, card_index1);
    printf("\n");

    printf("Second card picked: %c", myDeck.cards[card_index2].value);
    printCardSymbol(&myDeck, card_index2);
    printf("\n");

    // Step 5: call the checkForMatch function to see if the player has picked
    // a matching pair. If so, print the corresponding message & add the cards
    // to the player's winning pile (Player.winPile).
    if (checkForMatch(&myDeck, currentPlayer, userInput1[0],
                      userInput1[1], userInput2[0], userInput2[1]))
    {
      // Keep the current player as a match leads to an extra round.
      printf("\n%s has found a match! Earns an extra turn.\n",
             currentPlayer->name);
      addCardToPlayer(currentPlayer, &myDeck.cards[card_index1]);
      addCardToPlayer(currentPlayer, &myDeck.cards[card_index2]);
    }
    // Player hasn't found a match, so switch players.
    else
    {
      printf("\n%s has not found a match.\n", currentPlayer->name);
      // If the current player was Player 1, switch to Player 2.
      if (currentPlayer == &player1)
      {
        currentPlayer = &player2;
      }
      // Switch to Player 1
      else
      {
        currentPlayer = &player1;
      }
    }

  } while (!checkForWinner(&myDeck));

  // Step 6: find out who won the game and announce the winner
  printf("\n%s has won %d cards.\n", player1.name, player1.cardsWon);
  printf("%s has won %d cards.\n", player2.name, player2.cardsWon);

  // Player 1 has won
  if (player1.cardsWon > player2.cardsWon)
  {
    printf("%s has won!\n", player1.name);
  }
  // Player 2 has won
  else if (player1.cardsWon < player2.cardsWon)
  {
    printf("%s has won!\n", player2.name);
  }
  // Game is a tie
  else
  {
    puts("It's a tie!");
  }

  //Step 7: clean up player's winning piles
  clearPlayer(&player1);
  clearPlayer(&player2);

  return 0;
}