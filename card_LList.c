/*
Description: Implement a linked list structure where each node stores the 
address of a card from the Deck.
*/

#include "card_LList.h"

// A function that creates a new Card_LList, which is an empty linked list.
Card_LList *createCard_LList()
{
  // Allocate space for the new linked list and initialize, if successful.
  Card_LList *newlist = malloc(sizeof(Card_LList));
  if (newlist == NULL)
  {
    exit(0);
  }
  else
  {
    newlist->head = NULL;
    newlist->tail = NULL;
  }
  return newlist;
}

// A function that removes all the nodes from the list
// by freeing them one by one. The result is an empty linked list.
void clearCard_LList(Card_LList *theList)
{
  // Keep removing the front node until linked list becomes empty.
  while (!(isEmptyCard_LList(theList)))
  {
    removeFrontCard_LList(theList);
  }
}

// A function that checks if the list is empty.
// If it is empty, return true; otherwise return false.
bool isEmptyCard_LList(Card_LList *theList)
{
  if (theList->head == NULL || theList->tail == NULL)
  {
    return true;
  }
  return false;
}

// A function that inserts the card as a part of a node
// (the node itself doesn't store the card, but the address of the card).
void insertFrontCard_LList(Card_LList *theList, Card *theCard)
{
  // Allocate space for the new node
  Card_Node *current_card = malloc(sizeof(Card_Node));
  if (current_card == NULL)
  {
    exit(0);
  }
  else
  {
    // Set the node's card to the chosen card
    // Set the next pointer to NULL
    current_card->card = theCard;
    current_card->next = NULL;

    // If the tail is NULL, then the linked list is empty
    if (theList->tail == NULL)
    {
      theList->tail = current_card;
    }

    // If there is already at least one node in the linked list
    if (theList->head != NULL)
    {
      // Set the next pointer of the new node to point
      // to the node that was already in the front
      current_card->next = theList->head;
    }
    theList->head = current_card;
  }
}

// A function that inserts the card as a part of a node
// (the node itself doesn't store the card, but the address of the card).
void insertEndCard_LList(Card_LList *theList, Card *theCard)
{
  // Allocate space for the new node
  Card_Node *current_card = malloc(sizeof(Card_Node));
  if (current_card == NULL)
  {
    exit(0);
  }
  else
  {
    // Set the node's card to the chosen card
    // Set the next pointer to NULL
    current_card->card = theCard;
    current_card->next = NULL;

    // If the head is NULL, then the linked list is empty
    if (theList->head == NULL)
    {
      theList->head = current_card;
    }

    // If there is already at least one node in the linked list
    if (theList->tail != NULL)
    {
      // Set the next pointer of the tail node to
      // point to the new node
      theList->tail->next = current_card;
    }
    theList->tail = current_card;
  }
}

// A function that returns the address of the card stored in the node.
// Freeing of the node memory is done here.
Card *removeFrontCard_LList(Card_LList *theList)
{
  Card_Node *firstNode = theList->head;

  // If the linked list has at most one item
  if (theList->head == theList->tail)
  {
    theList->tail = NULL;
  }

  // Set the head pointer to point to the second node (if present),
  // otherwise it will point to NULL if there was only one node
  theList->head = firstNode->next;
  firstNode->next = NULL;

  Card *first_node_card = firstNode->card;

  // Free the front node and return the card associated with it
  free(firstNode);
  firstNode = NULL;
  return first_node_card;
}

// A function that returns the address of the card stored in the node.
// Freeing of the node memory is done here.
Card *removeEndCard_LList(Card_LList *theList)
{
  Card_Node *lastNode = theList->tail;

  // If the linked list has at most one item
  if (theList->head == theList->tail)
  {
    theList->head = NULL;
    theList->tail = NULL;
  }
  else
  {
    // Find the second last card
    Card_Node *second_last = theList->head;
    while (second_last->next != lastNode)
    {
      second_last = second_last->next;
    }
    // Set the second last card's next pointer to NULL
    // Tail points to this "second last" card now.
    second_last->next = NULL;
    theList->tail = second_last;
  }

  lastNode->next = NULL;

  Card *last_node_card = lastNode->card;

  // Free the front node and return the card associated with it
  free(lastNode);
  lastNode = NULL;
  return last_node_card;
}