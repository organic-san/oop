/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     BJackPlayer.cc
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct. 5, 1998: Created.
***************************************************************************/

/* $Log: BJackPlayer.cc,v $
 * */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

using namespace std;
#include <vector>
#include <iostream>
#include <algorithm>
#include "AnsiPrint.h"
#include "CardPat.h"
#include "BJackPlayer.h"

// default constructor: simply initialize the number of cards to 0

BJackPlayer::BJackPlayer(const char *player_name) {
  name = string(player_name);
}

// start the black jack game with a new card
void BJackPlayer::start(void) {
 auto table = Table::getInstance();
 auto newCard = table.getCard();
 cardList.push_back(newCard);
}

// add a new card to the current hand.
// need to protect the array from overflowing
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ :vector control
void BJackPlayer::addCard(Card newCard) {
  cardList.push_back(newCard);
}

// get the total points of the current hand in a black jack game
// cards with face vaules above 10 are treated as 10
// Ace's can be treated as 1 or 11 points

int BJackPlayer::totalPoints(void) const {
  int total = 0;
  for(auto c : cardList) {
    total += min((c.getPip() + 1), 10);
  }
  return total;
}

// set the status of the first card

void BJackPlayer::openFirstCard() {
  isOpenFirstCard = true;
}

// print the current hand to the screen graphically

void BJackPlayer::showCards() const {
  // how many card line
  for(int i = 0; i < (int(cardList.size() - 1) / kNCardPerRow + 1); i++) {

    // card height
    for(int j = 0; j < kCardHeight; j++) {

      // print name
      cout << (int(name.size()) > j ? name[j] : ' ') << " ";

      // how many cards in one line
      for(int k = 0; 
        k < min(kNCardPerRow, int(cardList.size() - i * kNCardPerRow)); 
        k++) {
        // set hidden and reset on and off
        bool hidden = false, reset = false;
        if(i * kNCardPerRow + k == 0 && !isOpenFirstCard) hidden = true;
        if(j == 0) reset = true;

        // print
        cardList[i * kNCardPerRow + k].print(hidden, reset);

        cout << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
}

