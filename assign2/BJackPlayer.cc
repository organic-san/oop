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
#include <iostream>
#include "AnsiPrint.h"
#include "CardPat.h"
#include "BJackPlayer.h"

// default constructor: simply initialize the number of cards to 0

BJackPlayer::BJackPlayer(const char *player_name) {

}

// start the black jack game with a new card
void
BJackPlayer::start(void) {

}

// add a new card to the current hand.
// need to protect the array from overflowing
void 
BJackPlayer::addCard(Card newCard) {

}

// get the total points of the current hand in a black jack game
// cards with face vaules above 10 are treated as 10
// Ace's can be treated as 1 or 11 points

int
BJackPlayer::totalPoints(void) const {

}

// set the status of the first card

void
BJackPlayer::openFirstCard() {

}

// print the current hand to the screen graphically

void 
BJackPlayer::showCards() const {
  
}

