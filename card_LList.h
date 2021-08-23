#ifndef A4_CARD_LLIST_H
#define A4_CARD_LLIST_H

#include <stdlib.h>
#include <stdbool.h>
//use the "forward declaration" technique so Card can be used here
typedef struct Card Card;

typedef struct Node {
  Card* card; //not a copy of the card, but the address of a card from a deck
  struct Node* next;
} Card_Node;

typedef struct {
  Card_Node* head;
  Card_Node* tail;
} Card_LList;

//a function that creates a new Card_LList, which is an empty linked list.
Card_LList* createCard_LList();

//a function that removes all the nodes from the list
// by freeing them one by one. The result is an empty linked list.
void clearCard_LList(Card_LList* theList);

//a function that checks if the list is empty.
// If it is empty, return true; otherwise return false.
bool isEmptyCard_LList(Card_LList* theList);

//a function that inserts the card as a part of a node
// (the node itself doesn't store the card, but the address of the card).
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
void insertFrontCard_LList(Card_LList* theList, Card* theCard);

//a function that inserts the card as a part of a node
// (the node itself doesn't store the card, but the address of the card).
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
void insertEndCard_LList(Card_LList* theList, Card* theCard);

//a function that returns the address of the card stored in the node.
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
// Freeing of the node memory is done here.
Card* removeFrontCard_LList(Card_LList* theList);

//a function that returns the address of the card stored in the node.
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
// Freeing of the node memory is done here.
Card* removeEndCard_LList(Card_LList* theList);

#endif
