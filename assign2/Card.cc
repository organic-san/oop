/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     Card.cc
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 5, 1998: Created.
***************************************************************************/

/* $Log: Card.cc,v $
 * */

using namespace std;
#include <iostream>
#include <assert.h>
#include "AnsiPrint.h"
#include "CardPat.h"
#include "Card.h"


// constructor
Card::Card(int myId)
: id(myId), line(0) {

}

// Accessor: card id is an integer between 0 and 51.
// Cards of the same pips are together.
// In other words, cards are in the following order:
//    1S 1H 1D 1C 2S 2H ...

int Card::getID() const {
  return id;
}


int Card::IDConverter(int suit, int pip) {
  return pip * 4 + suit;
}

// get the pip of the card (0-12)
int Card::getPip() const {
  return (id / 4);
}

// get the suit of the card (0-3)
int Card::getSuit() const {
  return (id % 4);
}

// print the suit name and face value of the card
// print one line when called one time
void Card::print(bool hidden, bool resetLine) const {
  if(resetLine) line = 0;

  if (line >= kCardHeight) {
    throw "err: Card::print(): lineNum bigger than " + to_string(kCardHeight) + ".";
  } else if(getPip() >= kNPip) {
    throw "err: Card::print(): cardNum bigger than " + to_string(kNPip) + ".";
  }

  //replace "x" to specific suit
  char replaceLetter = cardAbbrev[getSuit()];
  string t = card[hidden ? kCardType - 1 : getPip()][line];
  for (int i = 0; i < kCardWidth; i++) {
    if (t[i] == 'x') t[i] = replaceLetter;
  }
  AnsiPrint(t.c_str(), cardColor[getSuit()], white);
  line++;
  line = line % kCardHeight;
}
