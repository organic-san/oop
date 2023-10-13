/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     Card.h
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 5, 1998: Created.
***************************************************************************/

/* $Log: Card.h,v $
 *
 * */

#ifndef _CARD_H
#define _CARD_H

#include "AnsiPrint.h"

// a few card related constants
const int kNPip = 13;
const int kNSuit = 4;
// total number of cards for a standard deck of poker cards
const int kNCards = 52;
// four different suit names
const char* const suitName[] = { "spade", "heart", "diamond", "club" };
// data for use with the card printing
const char cardAbbrev[] = "SHDC";
// data for use with the card printing
const color cardColor[] = {black, red, red, black};
// maximal number of cards to be print in a row before wrapping
const int kNCardPerRow = 5;
// suit types
enum suit {spare, heart, diamond, club};

class Card {

public:
  // Constructor
  Card(int myId);
  
  // accessors
  int getID(void) const;
  int getPip(void) const; 
  int getSuit(void) const;
  
  // modifiers
  void setID(int newid);
    
    // print the face value and suit of the card
  void print(bool hidden, bool resetLine = false) const;

  // convert id from suit and pip
  static int IDConverter(int suit, int pip);

private:
  int id;
  mutable int line;
};

#endif
