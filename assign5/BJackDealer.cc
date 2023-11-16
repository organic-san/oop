/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     BJackDealer.cc
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 12, 1998: Created.
***************************************************************************/

/* $Log:$ */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
}

using namespace std;

#include <iostream>
#include "AnsiPrint.h"
#include "Card.h"
#include "BJackPlayer.h"
#include "BJackDealer.h"

// constructor 
// nDeck is the number of standard decks that the dealer will deal with
BJackDealer::BJackDealer(int nSet) 
: BJackPlayer("Dealer"), nSet(nSet) {

}

// distribute a card to the player
Card
BJackDealer::giveCard() {
  Card temp(dealCard());
  return temp;
}

// give the dealer as many cards as necessary to exceed the player 
// of the given total points
// A special case happen when both of them have 21 points.
// It is a tie game and therefore the dealer does not get more cards.

void
BJackDealer::addCards(int oppTotal) {
  while (judge(oppTotal) != win && totalPoints() <= kMaxPointInOneTurn) {
    addCard(giveCard());
  }
  
}

int BJackDealer::dealCard() {
  if(table.size() < 0) throw "err: Table::getCard(): no more card on the table.";
  auto iter = table.begin();
  int temp = *iter;
  table.erase(table.begin());
  return temp;
}

// Determine who has win the game.
// The total points that the dealer has should be greater than 
// the player at the point this function is called.

result
BJackDealer::judge(int oppTotal) const {
  const int myTotalPoints = totalPoints();
  if(oppTotal < kMaxPointInOneTurn && myTotalPoints < kMaxPointInOneTurn) {
    if(oppTotal < myTotalPoints)
      return win;
    else
      return lose;
  } else if(oppTotal > kMaxPointInOneTurn && myTotalPoints <= kMaxPointInOneTurn) {
    if(myTotalPoints >= kMinPointToWinWhenPlayerOverMaxPoint)
      return win;
    else
      return lose;
  } else if(oppTotal <= kMaxPointInOneTurn && myTotalPoints > kMaxPointInOneTurn) {
    return lose;
  } else {
    return tie;
  }
}

// start a new game
// before starting a new game, check if there are enough cards left for 
// the next game.

void
BJackDealer::start(void) {
  if(int(table.size()) < nSet * kMinCardsToStartGame) shuffle();
  nCards=0;
  showAll=false;
}

// shuffle the deck of cards
void 
BJackDealer::shuffle(void) {
  table.clear();
  for(int k = 0; k < nSet; k++) {
        for(int i = 0; i < kNSuit; i++) {
            for(int j = 0; j < kNPip; j++) {
                table.push_back((j * kNSuit + i) % (kMaxNCards));
            }
        }
    }

    for(int i = 0; i < kNSuit * kNPip * nSet; i++) {
        int index = rand() % (kNSuit * kNPip * nSet - i);
        table.push_back(table[index]);
        table.erase(table.begin() + index);
    }
}

// reset the seed before shuffling
void
BJackDealer::shuffle(long seed) {
  srand(seed);
  shuffle();
}

