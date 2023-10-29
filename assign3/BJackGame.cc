/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     BJackGame.cc
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 12, 1998: Created.
***************************************************************************/

/* $Log:$ */

#include <iostream>
#include "AnsiPrint.h"
#include "Card.h"
#include "BJackGame.h"
#include "BJackPlayer.h"
#include "BJackDealer.h"

using namespace std;

// only constructor
// Must be given a valid (initialized) game player and dealer
// Menu is constructed internally to provide basic text interface
// We must use an initialization list here.
BJackGame::BJackGame(BJackPlayer &bjp, BJackDealer &bjd) 
: menu(sizeof(menuItems)/sizeof(char *),menuItems), 
  bjplayer(bjp), bjdealer(bjd) {}

// one run of the game
// take and process a user action
// show current hands for both players at the end of a run.
bool
BJackGame::oneRun() {
  bjplayer.showCards();
  bjdealer.showCards();
  menu.print();
  int ans = menu.getAnswer();
  switch (ans) {
    case o_more: moreCard(); break;
    case o_enough: enough(); break;
    case o_restart: restart(); break;
    case o_quit: return false; break;
  }
  return true;
}

// give the player one more card
// check if we can do that first
void 
BJackGame::moreCard() {
    if(gameplayState == waiting) {
    cout << "Game is over. Choose '" << 
    menuItems[o_restart - 1] <<
    "' to restart a game." << endl;
    return;
  }

  if(bjplayer.totalPoints() > kMaxPointInOneTurn) {
    cout << "You are over " << kMaxPointInOneTurn <<" already" << endl;
    return;
  }

  bjplayer.addCard(bjdealer.giveCard());
}

// give the dealer enough cards to try to win the player
// determine who win the game at the end
void 
BJackGame::enough() {
  if(gameplayState == waiting) {
    cout << "Game is over. Choose '" << 
    menuItems[o_restart - 1] <<
    "' to restart a game." << endl;
    return;
  }

  bjdealer.addCards(bjplayer.totalPoints());
  bjdealer.openFirstCard();

  result r = bjdealer.judge(bjplayer.totalPoints());
  switch (r) {
    case win:
      cout << " win. Try again.";
      dealerCredit ++;
      playerCredit --;
      break;
    case lose:
      cout << "You win. Good job.";
      playerCredit ++;
      dealerCredit --;
      break;
    case tie:
      cout << "It's a Tie.";
      break;
  }

  cout << "(You have "<< playerCredit << " Credits," << 
  " I have " << dealerCredit << " Credits.)" << endl;
  gameplayState = waiting;
}

// restart the game by giving each player two new cards
// need to check if any one broke (bankrupt).
void 
BJackGame::restart() {
  if(playerCredit <= 0 || dealerCredit <= 0) {
    cout << "Sorry. Game over. No loan here." << endl;
    return;
  }
  if(gameplayState == playing) {
    cout << "Game is not over yet. Choose '" << 
    menuItems[o_enough - 1] <<
    "' to end a game." << endl;
    return;
  }
  bjdealer.start();
  bjplayer.start();
  bjdealer.addCard(bjdealer.giveCard());
  bjplayer.addCard(bjdealer.giveCard());
  bjdealer.addCard(bjdealer.giveCard());
  bjplayer.addCard(bjdealer.giveCard());
  bjplayer.openFirstCard();
  gameplayState = playing;
}

void 
BJackGame::quit() {}

