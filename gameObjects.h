#ifndef A4_GAMEOBJECTS_H
#define A4_GAMEOBJECTS_H

#define NUM_OF_CARDS_IN_DECK 52

#include <stdbool.h> //so bool can be used
#include <stdio.h> //so printf can be used
#include <stdlib.h> //so NULL and srand+rand can be used
#include "card_LList.h"

//definition of the enum suits to represent the 4 suits in cards
typedef enum {Spades, Hearts, Clubs, Diamonds} Suit;

//definition of a struct representing a card
//not using the typedef here for the "forward declaration" technique to work
struct Card {
  Suit suit;
  char value;
};

//definition of a struct representing a deck of cards
typedef struct {
  char* brand; //c string storing the brand name
  Card cards[NUM_OF_CARDS_IN_DECK]; //a deck has 52 cards
} Deck;

//definition of a struct representing a player
typedef struct {
  char* name;
  int cardsWon; //number of cards won by the player
  Card_LList winPile; //a linked list storing the cards won by the player
} Player;


//a function that initializes all the fields of a Deck.
// For each suit, the values of the cards are
// ‘A’, ‘2’, ‘3’, …, ‘9’, ,'T', ‘J’, ‘Q’, ‘K’.
void initializeDeck(Deck* theDeck, char* brandName);

//a function that shuffles the deck
void shuffleDeck(Deck* theDeck);

//a function that prints the content of a Deck.
//accepts a second bool parameter:
//if true, print face up, if false, print face down.
//if the card is won by a player, leave it blank.
void printDeck(const Deck* theDeck, bool faceUp);


//a function that initializes all the fields of a Player.
void initializePlayer(Player* thePlayer, char* theName);

//a function clears the winning pile of the player by calling the necessary
// function on a Card_LList.
void clearPlayer(Player* thePlayer);

#endif
