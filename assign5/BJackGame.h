/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     BJackGame.h
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 12, 1998: Created.
***************************************************************************/

/* $Log:$ */

#ifndef _BJACKGAME_H
#define _BJACKGAME_H

#include "ConsoleMenu.h"

// forward declaration
class BJackPlayer;
class BJackDealer;

// menu for actions that are used in the black jack game
const char * const menuItems[]={"One more Card",
				"Enough",
				"Restart",
				"Quit"};
enum option {o_more=1,o_enough,o_restart,o_quit};

// the black jack game
class BJackGame {

public:

  /**
   * constructor
   * require an initialized player and a dealer
   */
  BJackGame(BJackPlayer &bjp, BJackDealer &bjd);

  /**
   * one run of the game: return FALSE if quit
   * one run means taking and processing a user action
   */
  bool oneRun(void);

private:

    // routines to handle four actions
    // give the player one more card
    void moreCard();
    // give the dealer enough card and determine who wins
    void enough();
    // restart the game over
    void restart();
    // quitting the game
    void quit();
    
    // flag to indicate if we have a valid game
    bool over;
    
    // menu item strings
    ConsoleMenu menu;
    
    // references to a player and a dealer
    BJackPlayer &bjplayer;
    BJackDealer &bjdealer;

    // credits
    static const int initCredit=10;
    static const int betCredit=1;
    int playerCredit;
    int dealerCredit;

};

#endif
