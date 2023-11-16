/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     BJackPlayer.h
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 5, 1998: Created.
***************************************************************************/

/* $Log: BJackPlayer.h,v $
 * Revision 1.1  1998/10/05 18:43:36  li
 * Initial revision
 *
 * */

#ifndef _BJACKPLAYER_H
#define _BJACKPLAYER_H

/**
 * class to simulate a black jack game player
 * A black jack player 
 * 1. knows how to start a new game,
 * 2. add a new card to the current hand,
 * 3. compute the total of the current hand
 * 4. shows his/her cards to the screen with the first card facing up or down
 */

#include "Card.h"

class BJackPlayer {
    
public:

    // default constructor
    // all initialization should be in this constructor
    BJackPlayer(const char *name);
    
    /**
     * Start an empty hand
     */
    void start(void);
    
    /**
     * add a card to the end of the current hand
     */
    void addCard(Card newCard);
    
    /**
     * total of the face values of the cards at hand
     */
    int totalPoints(void) const;
    
    /**
     * open the first card so it faces up
     */
    void openFirstCard();

    /**
     * print all cards of the current hand to the screen 
     * It should check if the user has a valid hand first.
     */
    void showCards() const;
    
private:
    
    // your private/internal stuff goes here
    
    static const int kMaxCards=10; // maximal number of cards I can hold
    int nCards; // current number of cards at hand
    Card cards[kMaxCards]; // the current hand
    int showAll; // a flag indicating the first card is facing up or down  
    
    char *name;
    
};


#endif // _BJACKPLAYER_H


