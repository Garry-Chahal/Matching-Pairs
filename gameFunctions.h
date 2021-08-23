#ifndef A4_GAMEFUNCTIONS_H
#define A4_GAMEFUNCTIONS_H

#include <stdbool.h> //to be able to use bool
#include <stdlib.h>
#include <stdio.h>
#include "card_LList.h"
#include "gameObjects.h"

//a function that adds the card to the player's winning pile by calling
// the appropriate function from card_LList and update the cards won.
// Also marks the card as taken ('0').
void addCardToPlayer(Player* thePlayer, Card* theCard);

//a function that checks if the user choice is valid:
// if any of the choices are invalid, report that and return false.
bool checkPlayerInput(Deck* theDeck, Player* thePlayer, char row, char col);

//a function that checks if there is a match:
// if the two choices are the same, report it and return false.
// if there is a match, return true; otherwise, return false.
bool checkForMatch(Deck* theDeck, Player* thePlayer,
                      char r1, char c1, char r2, char c2);

//a function that checks if the game has a winner
// (all cards in the deck is taken)
bool checkForWinner(const Deck* theDeck);

#endif
