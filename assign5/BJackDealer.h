/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     BJackDealer.h
   PURPOSE
     class for simulating the dealer in a Black Jack card game
   NOTES
     You need to add some private stuff in this file.     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 12, 1998: Created.
***************************************************************************/

/* $Log:$ */

#ifndef _BJACKDEALER_H
#define _BJACKDEALER_H

// number of cards in a standard deck
const int kMaxNCards=52;
// result of a game
enum result {tie, win, lose};

// foreward declaration of class PokerPlayer
class BJackPlayer;

/**
 * The Dealer class simulate the dealer in a poker game.
 * It is responsible for 
 * 1. shuffling the cards, 
 * 2. draw and distribute a hand to a player and
 * 3. check if there is enough cards left for user request
 */

class BJackDealer {
    
public:
    
  /**
   * constructor: 
   * nSet is the number of decks of cards that you want the dealer 
   * to handle
   */
  
  BJackDealer(int nSet=1);
  
  /**
   * return a valid card ID to the player
   */
  int giveCard(void);
  
  /**
   * Give myself (the dealer) one more card
   */
  void addCard(void);
  
  /**
   * Give myself (the dealer) more cards in order to win the player
   * Input argument is the current points that the player has.
   */
  void addCards(int oppTotal);
  
  /**
   * Determine who has won the game 
   * Input argument is the current points that the player has.
   */
  result judge(int curOppTotal) const;
  
  /**
   * starting a new game
   */
  void start(void);
  
  /**
   * open the first card so it faces up
   */
  void openFirstCard();

  /**
   * retain the whole set of cards and shuffle 
   */
  void shuffle(void);
  
  /**
   * same as shuffle except for using a different seed for RNG
   */
  void shuffle(long seed);
  
  /**
   * show the dealer's cards to the screen
   */
  void showCards(void) const;
  
private:
  
  // your private or internal stuff goes here
  // flags indicating if a card has been drawn
  bool *cardsDealt;
  // total number of cards
  int nTotalCards;
  // number of cards left in the dealer's hand
  int cardLeft;
  
  // The dealer is a player as well.
  // Ideally, we should use inheritance that will be covered later
  // in this class.
  BJackPlayer dealer;
  
};

#endif // _BJACKDEALER_H
