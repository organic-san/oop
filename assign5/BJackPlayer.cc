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
 * Revision 1.1  1998/10/05 18:43:36  li
 * Initial revision
 *
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

  name = strdup(player_name);
  start();

}

// start the black jack game with a new card
void
BJackPlayer::start(void) {

    nCards=0;
    showAll=false;

}

// add a new card to the current hand.
// need to protect the array from overflowing
void 
BJackPlayer::addCard(Card newCard) {

    if (nCards < kMaxCards) {
	cards[nCards++]=newCard;
    } else {
	cout << "Error: Exceed the maximal number of cards a player can have." 
	     << endl;
    }

}

// get the total points of the current hand in a black jack game
// cards with face vaules above 10 are treated as 10
// Ace's can be treated as 1 or 11 points

int
BJackPlayer::totalPoints(void) const {

    int total=0;
    int point;
    int credit=0;

    for(int i=0; i<nCards; i++) {
	point=cards[i].getPip()+1;
	if (point==1) {
	    credit++;
	} else if (point>10) 
	    point=10;
	total += point;
    }
    
    // add points depending on how many aces we have
    for(int i=0; i<credit; i++) {
	if (total+10 <=  21) {
	    total += 10;
	} else {
	    break;
	}
    }

    return total;
}

void
BJackPlayer::openFirstCard() {

    showAll=true;

}

inline int 
Min(int i, int j) {
  return (i<j)? i:j; 
}

// print the current hand to the screen graphically

void 
BJackPlayer::showCards() const {
  
  unsigned char s,p;
  char line[kCardWidth+1];
  int curCard=0, lastCard;
  
  while(curCard < nCards) {
    for(unsigned int i=0;i<kCardHeight;i++) {
      lastCard = Min(curCard+kNCardPerRow, nCards);
      if (i < strlen(name)) {
	cout << name[i] << " ";
      } else {
	cout << "  ";
      }
      for(int j=curCard;j<lastCard;j++) {
	s=cards[j].getID()%kNSuit;
	p=cards[j].getID()/kNSuit;
	if ((j==0)&&(showAll==false)) 
	    p=13;
	for(int k=0;k<kCardWidth;k++) {
	  line[k]=card[p][i][k];
	  if (line[k]=='x') 
	    line[k]=cardAbbrev[s];
	}
	line[kCardWidth]='\0';
	AnsiPrint(line,cardColor[s],white);
	cout << " ";
      }
      cout << endl;
    }
    curCard=lastCard;
  }
}
